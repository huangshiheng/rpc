cc=g++
all:client.o eventLoop.o rpcServer.o rpcSocket.o serverStream.o
	ar crv librpc.a client.o eventLoop.o rpcServer.o rpcSocket.o serverStream.o
	mv librpc.a ../output/lib
	cp *.h ../output/include
	rm client.o eventLoop.o rpcServer.o rpcSocket.o serverStream.o
client.o:
	${cc} -c client.cpp -std=c++11
eventLoop.o:
	${cc} -c eventLoop.cpp -std=c++11
rpcServer.o:
	${cc} -c rpcServer.cpp -std=c++11
rpcSocket.o:
	${cc} -c rpcSocket.cpp -std=c++11
serverStream.o:
	${cc} -c serverStream.cpp -std=c++11
clean:
	rm client.o eventLoop.o rpcServer.o rpcSocket.o serverStream.o
