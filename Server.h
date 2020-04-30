#ifndef SERVER_H
#define SERVER_H

#include "Common.h"

class Server{

public:
	Server();

	//Initiate and configure Server 
	void init();

	//close server
	void close();

	//start running server
	void start();

private:
	int sendBroadcastMessage(int clientfd);

	// server address info
	struct sockaddr_in severAddr;

	// socket listening
	int listener;

	int epfd;

	//list of clients
	list<int> clients_list;

};

#endif
