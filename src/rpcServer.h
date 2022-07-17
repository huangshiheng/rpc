/*************************************************************************
	> File Name: rpcServer.h
	> Author: 黄仕恒
	> Mail: 2751977980@qq.com
	> Created Time: Sat 19 Feb 2022 11:17:54 PM CST
 ************************************************************************/
#pragma once

#include "rpcSocket.h"
#include "eventLoop.h"
#include "serverStream.h"

namespace rpc {

    class rpcServer {
        public:
            rpcServer() { 
                socket = new Socket();
            }
            ~rpcServer() {
                socket->~Socket();
            }

            rpcServer(Socket* sock) : socket(sock) { }

            int doBind(std::string& host, int port);
            
            int doListen(std::string& host, int port);

            int doAccept(int fd);

        private:
            Socket* socket;
    };

}


