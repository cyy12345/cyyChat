#ifndef SERVER_H
#define SERVER_H

#include "Common.h"
using namespace std;

class Server{

public:
	Server();

	//Initiate and configure Server 
	void init();

	//close server
	void Close();

	//start running server
	void start();

private:
	int sendBroadcastMessage(int clientfd);

	// server address info
	struct sockaddr_in serverAddr;

	// socket listening
	int listener;

	int epfd;

	int name_ep;

	//list of clients
	list<int> clients_list;

	unordered_map<int,string> client_map;

};

#endif
