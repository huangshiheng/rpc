cc=g++
all:
	cp /usr/local/protobuf/lib/libprotobuf.a .
	${cc} -o client myClient.cpp -I /usr/local/protobuf/include/ -L . -L ../output/lib -lrpc -lrpcpb -lprotobuf -lpthread -std=c++11
	${cc} -o server myServer.cpp -I /usr/local/protobuf/include/ -L . -L ../output/lib -lrpc -lrpcpb -lprotobuf -lpthread -std=c++11
clean:
	rm -rf client server librpc.a libprotobuf.a librpcpb.a trpc