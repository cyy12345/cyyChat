#include "Server.h"

using namespace std;

Server::Server(){
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	listener = 0;

	epfd = 0;

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

	if(epfd < 0){
		perror("epfd error");
		exit(-1);
	}

	addfd(epfd, listener, true);    // add the listening event into the epoll event list

}

void Server::start(){

	static struct epoll_event events[EPOLL_SIZE];

	init();

	while(1){

	}
}
