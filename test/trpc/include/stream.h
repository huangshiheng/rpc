/*************************************************************************
	> File Name: stream.h
	> Author: 黄仕恒
	> Mail: 2751977980@qq.com
	> Created Time: Sun 20 Feb 2022 10:19:08 AM CST
 ************************************************************************/

#pragma once

#include "rpcSocket.h"


namespace rpc {

    class Stream {
        public:
            Stream() { }

            virtual int doWrite() { }
            virtual int doRead() { }
            virtual void setData(std::string& data) { }
            virtual void getData(std::string& data) { }

        private:
    
    };



}
