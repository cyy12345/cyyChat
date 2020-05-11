#include "Server.h"

using namespace std;

Server::Server(){
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	listener = 0;

	epfd = 0;
//	name_ep = 0;

}

void Server::init(){
	cout << "*** Init Server ..." << endl;
	listener = socket(AF_INET, SOCK_STREAM, 0);

	if(listener < 0){
		perror("Creating listener failed.");
		exit(-1);
	}

	if(bind(listener,(struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0){
		perror("bind error");
		exit(-1);
	}

	int ret = listen(listener, 5);
	if(ret < 0){
		perror("listen error");
		exit(-1);
	}

	cout << "*** Start to listen: " << SERVER_IP << endl;

	epfd = epoll_create(EPOLL_SIZE);   // first step of epoll, create the handle
//	name_ep = epoll_create(1);

	if(epfd < 0){
		perror("epfd error");
		exit(-1);
	}

	addfd(epfd, listener, true);    // add the listening event into the epoll event list

}

void Server::Close(){
	close(listener);
	close(epfd);
}

int Server::sendBroadcastMessage(int clientfd){
	char buf[BUF_SIZE], message[BUF_SIZE];
	memset(buf,0,BUF_SIZE);
	memset(message, 0, BUF_SIZE);

	//receive new message
	int len = recv(clientfd, buf, BUF_SIZE,0);
	//cout << buf << endl;
	
	//if(len !=0 && strlen(buf) == 0){
	//	return len;
	//}
	
	cout << "read from client(clientID = " << clientfd << ")" << endl;
	//cout << "the length of the received message: "<< len << endl;

	// if client closed the connection
	if(len == 0){
		close(clientfd);

		clients_list.remove(clientfd);
        cout << "ClientID = " << clientfd
             << " closed.\n now there are "
             << clients_list.size()
             << " client in the chat room"
             << endl;

	}else{
		if(clients_list.size() == 1){
			send(clientfd,CAUTION, strlen(CAUTION), 0);
			return len;
		}
		
		sprintf(message, SERVER_MESSAGE, client_map[clientfd].c_str(), buf);

		list<int>::iterator it;
		for(it = clients_list.begin(); it != clients_list.end();++it){
			if(*it != clientfd){
				if(send(*it,message, strlen(message),0) < 0){
					return -1;
				}
			}
		}
	}
	return len;
}

void Server::start(){

	static struct epoll_event events[EPOLL_SIZE];
//	static struct epoll_event login_event[1];
	init();

	while(1){
		int epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);

		if(epoll_events_count < 0){
			perror("epoll wait failure.");
			break;
		}

		//cout << "**** epoll events number: " << epoll_events_count << endl;

		for(int i = 0; i < epoll_events_count; ++i){
			int sockfd = events[i].data.fd;
			
			//new client connecting
			if(sockfd == listener){
				struct sockaddr_in client_address;
				socklen_t client_addrLength = sizeof(struct sockaddr_in);
				int clientfd = accept(listener, (struct sockaddr*)&client_address, &client_addrLength);
				
				struct clientInfo ci;
				int len = recv(clientfd, (void*)&ci, sizeof(ci),0);
				if(len <= 0){
					perror("login error");
					Close();
					exit(-1);
				}

				cout << "client connection from: "
					 << inet_ntoa(client_address.sin_addr) << ":"
					 << ntohs(client_address.sin_port) << ", clientfd = "
					 << clientfd << endl;
				
				addfd(epfd, clientfd, true);
				//addfd(name_ep, clientfd, true);

				clients_list.push_back(clientfd);
				cout << "Add new clientfd = " << clientfd << " to epoll" << endl;
				cout << "Now there are " << clients_list.size() << " clients in the chat room" << endl;

				/*
				epoll_wait(name_ep, login_event, 1, -1);
				struct clientInfo ci;
				if(login_event[0].data.fd == clientfd){
					cout << "read client info from client(clientID = " << clientfd << ")" << endl;
					int len = recv(clientfd, (void*)&ci, sizeof(ci),0);
					if(len <= 0){
						perror("login error");
						Close();
						exit(-1);
					}
				}
				*/	
				cout << "welcome message" << endl;
				char message[BUF_SIZE];

				memset(message,0,BUF_SIZE);
				client_map[clientfd] = string(ci.username);

				int ret = send(clientfd, message, strlen(message), 0);
				if(ret < 0){
					perror("send error");
					Close();
					exit(-1);
				}
			// existing client send message
			}else{
				int ret = sendBroadcastMessage(sockfd);
				if(ret < 0){
					perror("broadcast error");
					Close();
					exit(-1);
				}
			}
		}


	}
	Close();
}


