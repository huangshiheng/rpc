/*************************************************************************
	> File Name: rpcSocket.h
	> Author: 黄仕恒
	> Mail: 2751977980@qq.com
	> Created Time: Sat 19 Feb 2022 10:28:48 PM CST
 ************************************************************************/
#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string>

namespace rpc {

    class Socket {
        public:
            Socket() { }
            Socket(int sock) : socket_id(sock) { }
            ~Socket() { }
            int getSocketID() {
                return socket_id;
            }
            void setSocketID(int sock) {
                socket_id = sock;
            }
            int Write(std::string& s);
            int Read(std::string& s);
        private:
            int socket_id;
        
    };

}



