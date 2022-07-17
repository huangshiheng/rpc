/*
 * @filePath: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-07-03 16:10:40
 * @LastEditTime: 2022-07-16 14:28:53
 */

#include "../output/include/client.h"
#include "../output/include/eventLoop.h"
#include "../output/include/service.pb.pb.h"
#include <string>
#include <thread>

void func(rpc::clientStream* cli);
void work();

int main(int argc, char** argv) {
    std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;
    rpc::eventLoop* event_loop = rpc::eventLoop::getInstance();
    std::thread th(work);
    th.detach();
    event_loop->run();
    return 0;
}

void func(rpc::clientStream* cli) {
    std::cout << "func thread id: " << std::this_thread::get_id() << std::endl;
    std::string s;
    cli->getData(s);
    rpc::rpcResponce res;
    res.ParseFromString(s);
    if(res.has_msg()) {
        std::cout << "client read : " << res.msg() << std::endl;
    }
    rpc::eventLoop::getInstance()->stop();
}

void work() {
    std::cout << "work thread id: " << std::this_thread::get_id() << std::endl;
    rpc::clientStream* client = new rpc::clientStream();
    std::string host = "127.0.0.1";
    client->doConnect(host, 1234);

    std::string s = "This is Client!";
    std::string s1;
    rpc::rpcRequest re;
    re.set_head(2);
    re.set_msg(s);
    re.SerializeToString(&s1);
    client->setData(s1, func); // func是回调函数
    client->wait();
    std::cout << "client work end" << std::endl;
}
