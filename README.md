# rpc

## 目录
### pb
pb协议，给server和client传输使用
### protocol
传输协议 例如HTTP，pb协议序列化之后的二进制是传输协议的内容
### src
rpc的主要代码<br>
客户端和服务端都使用epoll机制来发送和接收数据<br>
eventLoop: 封装epoll<br>
rpcServer: 监听一个端口的server，如果有多个端口就有多个该类的实例<br>
rpcSocket: socket，有一个监听端口就有一个该类的实例，该类中的读写并没有使用<br>
stream: clientStream和serverStream的基类<br>
clientStream: 客户端连接服务端的流，客户端连接一个服务器就会有这个流，客户端的读写在该类实现；客户端连接到服务端之后，通过setData函数设置要传输的数据和回调函数的地址，然后将该连接描述符加入epoll，最后启动,支持同步和异步调用<br>
epoll；客户端通过epoll收到数据之后，跳到回调函数执行，执行完回调函数之后，客户度关闭连接描述符，将该描述符从epoll中删除<br>
serverStream: 服务端连接客户端的流，服务端的读写在该类实现；通过epoll接受数据之后，使用事件分发，让对应的服务处理该连接事件，之后将响应数据返回<br>
eventDispatcher: 事件分发器的基类，在eventLoop中被使用，因为事件分发器需要解析客户端传来的数据，但我不想在src中添加protobuf的代码，在src中不依赖任何库，所有，在外部实现eventDispatcher的子类传入eventLoop<br>
### test
测试代码<br>



git push出现下面错误，用下面的链接解决 Missing or invalid credentials<br>
https://juejin.cn/post/7062237873570840589


