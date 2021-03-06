#ifndef CLIENT_H
#define CLIENT_H

#include "Common.h"

class Client{
public:
	Client();
	void Connect(clientInfo& ci, std::string& server_ip, int server_port);
	void Close();
	void start();

private:
	int sock;

	int pid;

	int epfd;

	int pipe_fd[2];

	bool isClientwork;

	char message[BUF_SIZE];

	struct sockaddr_in serverAddr;
};

#endif
