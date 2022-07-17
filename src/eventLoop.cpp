/*************************************************************************
	> File Name: eventLop.cpp
	> Author: 黄仕恒
	> Mail: 2751977980@qq.com
	> Created Time: Sat 19 Feb 2022 10:47:27 PM CST
 ************************************************************************/

#include "eventLoop.h"
#include <iostream>

namespace rpc {

    eventLoop* eventLoop::instance = nullptr;

    eventLoop::eventLoop() {
        eventfd = epoll_create(1000);
        shutdown = false;
        dispater = nullptr;
    }

    int eventLoop::addEvent(int events, int fd) {
        struct epoll_event ev;
        ev.events = events;
        ev.data.fd = fd;
        return epoll_ctl(eventfd, EPOLL_CTL_ADD, fd, &ev);
    }

    int eventLoop::deleteEvent(int events, int fd) {
        struct epoll_event ev;
        ev.events = events;
        ev.data.fd = fd;
        return epoll_ctl(eventfd, EPOLL_CTL_DEL, fd, &ev);
    }

    int eventLoop::modifyEvent(int events, int fd) {
        struct epoll_event ev;
        ev.events = events;
        ev.data.fd = fd;
        return epoll_ctl(eventfd, EPOLL_CTL_MOD, fd, &ev);
    }

    void eventLoop::handerEvent(int eventfd, ::epoll_event* events, int nfds) {
        for (int i = 0; i < nfds; i++) {
            int fd;
            fd = events[i].data.fd;

            if(server.find(fd) != server.end()) { // 创建连接
                handerAccpet(fd);
                continue;
            }

            if(events[i].events & EPOLLIN) {
                handerIN(fd);
            }

            if(events[i].events & EPOLLOUT) {
                handerOUT(fd);
            }
        }
    }

    void eventLoop::handerAccpet(int fd) {
        rpcServer* ser = server[fd];
        int connfd = ser->doAccept(fd);
        serverStream *stream = new serverStream(connfd);
        stream->setDispatcher(dispater);
        addStream(connfd, stream);
        addEvent(EPOLLIN | EPOLLET, connfd);
    }

    void eventLoop::handerIN(int fd) {
        Stream* st = stream.find(fd)->second;
        int len = st->doRead();
        if(len <= 0) {
            close(fd);
            stream.erase(fd);
            std::cout << "Client close the connection" << std::endl;
        }
    }

    void eventLoop::handerOUT(int fd) {
        Stream* st = stream.find(fd)->second;
        int len = st->doWrite();
        modifyEvent(EPOLLIN | EPOLLET,fd);
    }

    int eventLoop::run() {
        ::epoll_event events[32000];
        while(!shutdown) {
            int nfds = epoll_wait(eventfd, events, 32000, -1);
            if(nfds == -1) {
                return -1;
            }
            handerEvent(eventfd, events, nfds);
        }
    }

    void eventLoop::setDispatcher(void (*dp)(serverStream* ser)) {
        dispater = dp;
    }

}

