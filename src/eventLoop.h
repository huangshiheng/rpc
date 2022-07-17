/*************************************************************************
	> File Name: eventLoop.h
	> Author: 黄仕恒
	> Mail: 2751977980@qq.com
	> Created Time: Sat 19 Feb 2022 10:38:46 PM CST
 ************************************************************************/

#pragma once

#include "rpcSocket.h"
#include "rpcServer.h"
#include "serverStream.h"
#include <unordered_map>

namespace rpc {
    class rpcServer;
    class serverStream;
    class eventLoop{
        public:
            int addEvent(int events, int fd);
            int deleteEvent(int events, int fd);
            int modifyEvent(int events, int fd);
            
            int run();

            void addStream(int fd, Stream* st) {
                stream[fd] = st;
            }

            void addServer(int fd, rpcServer* rs) {
                server[fd] = rs;
            } 

            void handerEvent(int eventfd, ::epoll_event* events, int nfds);

            void handerAccpet(int fd);

            void handerIN(int fd);

            void handerOUT(int fd);

            void setDispatcher(void (*dp)(serverStream* ser));

            static eventLoop* getInstance() {
                if(instance == nullptr) {
                    instance = new eventLoop();
                }
                return instance;
            }

            void stop() {
                shutdown = true;
            }

            void start() {
                shutdown = false;
            }

        private:
            eventLoop();
            int eventfd;
            bool shutdown;
            static eventLoop* instance;
            void (*dispater)(serverStream* ser); //  void (*on_success)(clientStream* cli); 
            std::unordered_map<int, rpcServer* > server; // socket与rpcServer一一对应
            std::unordered_map<int, Stream* > stream;    // 文件描述符与Socket一一对应
    };

}

