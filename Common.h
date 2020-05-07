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

static const unsigned int SERVER_PORT = 8888;

static const char *SERVER_IP = "127.0.0.1";

static const int EPOLL_SIZE = 5000;

static const int BUF_SIZE = 65535;

static const char* SERVER_WELCOME = "Welcome you join to the chat room! Your chat ID is: Client #%d"; 

static const char* CAUTION = "There is only one int the char room!";

static const char* SERVER_MESSAGE =  "ClientID %d say >> %s"; 

static const char* EXIT = "EXIT";

static void addfd(int epollfd, int fd, bool enable_et){
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	if(enable_et){
		ev.events = EPOLLIN | EPOLLET;  //enable edge trigger
	}
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);

	fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
	std::cout << "fd added to epoll!" << std::endl;
	std::cout << std::endl;
}

#endif
