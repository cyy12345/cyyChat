#include "Client.h"

using namespace std;

Client::Client(){
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	sock = 0;

	pid = 0;

	isClientwork = true;

	epfd = 0;

}

void Client::Connect(clientInfo& ci, std::string& server_ip, int server_port){
	cout << "Connect Server: " << server_ip << " : " << server_port << endl;

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0){
		perror("sock error");
		exit(-1);
	}

	if(connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0){
		perror("connect error");
		exit(-1);
	}
	int len = send(sock, (void*)&ci,sizeof(clientInfo),0);
	
	if(len < 0){
		perror("login error");
		exit(-1);
	}

	if(pipe(pipe_fd) < 0){
		perror("pipe error");
		exit(-1);
	}

	epfd = epoll_create(EPOLL_SIZE);

	if(epfd < 0){
		perror("epfd errpr");
		exit(-1);
	}

	addfd(epfd, sock, true);
	addfd(epfd, pipe_fd[0], true);

}

void Client::Close(){
	if(pid){
		close(pipe_fd[0]);
		close(sock);
	}else{
		close(pipe_fd[1]);
	}
}

void Client::start(){
	static struct epoll_event events[2];
	
	cout << "Please input server ip address: " << endl;

	string server_ip;
	cin >> server_ip;
	cout << "Please input server port: " << endl;
	
	int server_port;
	cin >> server_port;
	serverAddr.sin_port = htons(server_port);
	serverAddr.sin_addr.s_addr = inet_addr(server_ip.c_str());

	cout << "Please input your username: " << endl;
	clientInfo ci; 
	string username;
	//getline(cin,username);
	cin >> username;
	strcpy(ci.username,username.c_str());

	//ci.username[strlen(ci.username)-1] = 0;

	Connect(ci,server_ip,server_port);

	pid = fork();

	if(pid < 0){
		perror("fork error");
		close(sock);
		exit(-1);
	}else if(pid == 0){ //child process
		//start to write into the pipe, close the read end
		close(pipe_fd[0]);

		cout << "Please input 'exit' to exit the chat room" << endl;

		while(isClientwork){
			memset(message, 0, BUF_SIZE);
			fgets(message, BUF_SIZE, stdin);

			if(strncasecmp(message, EXIT, strlen(EXIT)) == 0){
				isClientwork = 0;
			}else{
				if(write(pipe_fd[1], message, strlen(message)-1) < 0){
					perror("write error");
					exit(-1);
				}
			}

		}
	}else{
		//parent process
		// may need a lock to work together with the child process
		// otherwise the two ends of the pipe would be closed
		close(pipe_fd[1]);

		while(isClientwork){
			int epoll_events_count = epoll_wait(epfd, events, 2, -1);

			for(int i = 0; i < epoll_events_count; ++i){
				memset(message, 0, BUF_SIZE);

				if(events[i].data.fd == sock){
					int ret = recv(sock, message, BUF_SIZE, 0);

					if(ret == 0){
						cout << "Server closed connection: " << sock << endl;
						close(sock);
						isClientwork = 0;
					}else{
						cout << message << endl;
					}
				}else{
					int ret = read(events[i].data.fd, message, BUF_SIZE);
					if(ret == 0){
						isClientwork = 0;
					}else{
						send(sock, message, BUF_SIZE, 0);
					}
				}
			}
		}
	}
	Close();
}
