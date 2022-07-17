/*************************************************************************
	> File Name: serverStream.h
	> Author: 黄仕恒
	> Mail: 2751977980@qq.com
	> Created Time: Sun 20 Feb 2022 10:23:48 AM CST
 ************************************************************************/

#pragma once

#include "rpcSocket.h"
#include "stream.h"
#include "eventLoop.h"

namespace rpc {

    class serverStream : public Stream {
        public:
            serverStream() { }
            serverStream(int fd) : connfd(fd) { }

            int doWrite();

            int doRead();

            virtual void setData(std::string& data);

            virtual void getData(std::string& data);

            void setDispatcher(void (*dp)(serverStream* ser)) {
                dispater = dp;
            }

            char buff[1024];

        private:
            int connfd;
            void (*dispater)(serverStream* ser);
    };

}


