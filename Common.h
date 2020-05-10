#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <list>
#include <sys/types.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>

static const unsigned int SERVER_PORT = 8888;

static const char *SERVER_IP = "0.0.0.0";

static const int EPOLL_SIZE = 5000;

static const int BUF_SIZE = 65535;

static const int NAME_SIZE = 20;

static const char* SERVER_WELCOME = "Welcome to join the chat room! Your chat username is: %s"; 

static const char* CAUTION = "There is only one user in the chat room!";

static const char* SERVER_MESSAGE =  " %s say >> %s"; 

static const char* EXIT = "EXIT";

struct clientInfo{
	char username[NAME_SIZE] = {0};
	int flag = 0;
};

static void addfd(int epollfd, int fd, bool enable_et){
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
//	if(enable_et){
//		ev.events = EPOLLIN | EPOLLET;  //enable edge trigger
//	}
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);

	//fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
	std::cout << "fd added to epoll!" << std::endl;
	std::cout << std::endl;
}

#endif
