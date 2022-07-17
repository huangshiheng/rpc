/*
 * @Autor: huangshiheng
 * @Date: 2022-07-09 11:00:50
 * @LastEditTime: 2022-07-16 14:21:56
 * @LastEditors: Please set LastEditors
 */

#pragma once

#include "rpcSocket.h"
#include "stream.h"
#include "eventLoop.h"

namespace rpc {

    class clientStream : public Stream {
        public :
            clientStream() {
                hasRead = true;
            }
            ~clientStream() {
                closeConn();
            }

            void doConnect(std::string& ip, int port);

            int doWrite();

            int doRead();

            void setData(std::string& data, void (*func)(clientStream* cli));

            void getData(std::string& data);

            void wait();

            char buff[1024];
        private:
            int connfd;
            void (*on_success)(clientStream* cli);
            void closeConn();
            bool hasRead;
    };

}