/*
 * @filePath: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-07-03 16:02:57
 * @LastEditTime: 2022-07-09 14:16:34
 */
/*************************************************************************
	> File Name: serverStream.cpp
	> Author: 黄仕恒
	> Mail: 2751977980@qq.com
	> Created Time: Sun 20 Feb 2022 10:23:48 AM CST
 ************************************************************************/

#include "serverStream.h"
#include <string.h>
#include <iostream>

namespace rpc {

	int serverStream::doWrite() {
        int len = write(connfd, buff, strlen(buff));
        close(connfd);
        eventLoop::getInstance()->deleteEvent(EPOLLIN | EPOLLET, connfd);
        return len;
	}
    
	int serverStream::doRead() {
		memset(buff, 0, sizeof(buff));
        int len = read(connfd, buff, 1024);
        if(dispater != nullptr) { /* server's dispatcher */
            dispater(this);
        }
        return len;
	}

    void serverStream::setData(std::string& data){
        memset(buff, 0, sizeof(buff));
        memcpy(buff, data.c_str(), data.length());
        eventLoop::getInstance()->modifyEvent(EPOLLOUT | EPOLLET, connfd);
    }

    void serverStream::getData(std::string& data){
        data = std::string(buff);
    }
}


