/*
 * @Autor: huangshiheng
 * @Date: 2022-07-09 14:17:12
 * @LastEditTime: 2022-07-16 14:28:22
 * @LastEditors: Please set LastEditors
 */

#include "../output/include/eventLoop.h"
#include "../output/include/rpcServer.h"
#include "../output/include/service.pb.pb.h"
#include "../output/include/serverStream.h"

void doDispatcher(rpc::serverStream* stream) {
                std::string s;
                stream->getData(s);
                rpc::rpcRequest re;
                re.ParseFromString(s);
                if(re.has_head()) {
                    std::cout << "server read : " << re.head() << std::endl;
                }
                if(re.has_msg()) {
                    std::cout << "server read : " << re.msg() << std::endl;
                }
                
                rpc::rpcResponce res;
                std::string s1 = "This is Server";
                res.set_msg(s1);
                std::string sx;
                res.SerializeToString(&sx);
                stream->setData(sx);
}

int main(int argc, char** argv) {
    rpc::eventLoop* event_loop = rpc::eventLoop::getInstance();
    rpc::rpcServer* server = new rpc::rpcServer();
    event_loop->setDispatcher(doDispatcher);
    std::string host = "127.0.0.1";
    server->doListen(host, 1234);
    event_loop->run();
    return 0;
}