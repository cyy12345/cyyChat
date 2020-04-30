#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <list>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netinet/in.h>


static const unsigned int SERVER_PORT = 8888;

static const string SEVER_IP = "127.0.0.1";

static const int EPOLL_SIZE = 5000;

static void addfd(int epollfd, int fd, bool enable_et){
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	if(enable_et){
		ev.events = EPOLLIN | EPOLLET;  //enable edge trigger
	}
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);

	fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
	cout << "fd added to epoll!" << endl;
}

#endif
