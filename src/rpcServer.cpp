/*************************************************************************
	> File Name: rpcServer.cpp
	> Author: 黄仕恒
	> Mail: 2751977980@qq.com
	> Created Time: Sat 19 Feb 2022 11:17:54 PM CST
 ************************************************************************/

#include "rpcServer.h"
#include <iostream>
#include <strings.h>

namespace rpc {

    int rpcServer::doBind(std::string& host, int port) {
        int listenfd;
        if((listenfd = ::socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            exit(1);
        }
        socket->setSocketID(listenfd);
        ::sockaddr_in addr;
        ::bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(host.c_str());
        int err;
        if((err = ::bind(listenfd, (struct sockaddr*)&addr, sizeof(addr))) < 0) {
            return err;
        }
        return 0;
    }

    int rpcServer::doListen(std::string& host, int port) {
        int err = doBind(host, port);
        std::cout << "server bind success " << std::endl;
        if(err < 0) {
            return err;
        }
        if((err = ::listen(socket->getSocketID(), 20)) < 0) {
            return err;
        }
        std::cout << "server is listening ... " << std::endl;
        eventLoop::getInstance()->addServer(socket->getSocketID(), this);
        err = eventLoop::getInstance()->addEvent(EPOLLIN, socket->getSocketID());
        if(err < 0) {
            return err;
        }
        return 0;
    }

    int rpcServer::doAccept(int fd) {
        int connfd = 0;
        struct sockaddr_in cliaddr;
        socklen_t cliaddrlen = sizeof(cliaddr);
        connfd = ::accept(fd, (struct sockaddr*)&cliaddr, &cliaddrlen);
        std::cout << "server connect " << inet_ntoa(cliaddr.sin_addr) << " : " << cliaddr.sin_port << std::endl;
        return connfd;
    }

}


