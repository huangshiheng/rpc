/*************************************************************************
	> File Name: rpcSocket.cpp
	> Author: 黄仕恒
	> Mail: 2751977980@qq.com
	> Created Time: Sat 19 Feb 2022 10:33:03 PM CST
 ************************************************************************/

#include "rpcSocket.h"

namespace rpc {
    
    int Socket::Write(std::string& s) {
        return write(socket_id, s.c_str(), s.length()); 
    }

    int Socket::Read(std::string& s) {
        char buff[1024];
        int len = read(socket_id, buff, 1024);
        s = std::string(buff);
        return len;
    }

}

