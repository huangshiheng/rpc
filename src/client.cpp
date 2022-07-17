/*
 * @filePath: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-07-03 15:31:55
 * @LastEditTime: 2022-07-16 14:31:18
 */

#include "client.h"
#include <string.h>
#include <iostream>

namespace rpc {

    int clientStream::doWrite() {
        int len = write(connfd, buff, strlen(buff));
        std::cout << "Client write : " << std::string(buff) << std::endl;
        eventLoop::getInstance()->modifyEvent(EPOLLIN | EPOLLET, connfd);
        return len;
    }

    int clientStream::doRead() {
        memset(buff, 0, sizeof(buff));
        int len = read(connfd, buff, 1024);
        hasRead = true;
        eventLoop::getInstance()->deleteEvent(EPOLLIN | EPOLLET, connfd);
        std::cout << "client close" << std::endl;
        if(on_success) {
            on_success(this);
        }
        return len;
    }

    void clientStream::doConnect(std::string& ip, int port) {
        int clientfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        struct sockaddr_in serv_addr;
        ::bzero((char*)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(ip.c_str());
        serv_addr.sin_port = htons(port);
        int err = 0;
        if((err = ::connect(clientfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
            return ;
        }
        std::cout << "Client connect success " << std::endl;
        eventLoop* event_loop = eventLoop::getInstance();
        connfd = clientfd;
        event_loop->addStream(connfd, this);
    }

    void clientStream::setData(std::string& data, void (*func)(clientStream* cli)){
        memset(buff, 0, sizeof(buff));
        memcpy(buff, data.c_str(), data.length());
        on_success = func;
        hasRead = false;
        eventLoop::getInstance()->addEvent(EPOLLOUT | EPOLLET, connfd);
    }

    void clientStream::getData(std::string& data){
        data = std::string(buff);
    }

    void clientStream::closeConn() {
        close(connfd);
    }

    void clientStream::wait() {
        while(!hasRead);
    }
}