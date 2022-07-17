cc=g++
all:service.pb.pb.o
	ar crv librpcpb.a service.pb.pb.o
	mv librpcpb.a ../output/lib
	cp *.h ../output/include
	rm service.pb.pb.*
service.pb.pb.o:
	/usr/local/protobuf/bin/protoc --cpp_out=./ service.pb
	${cc} -c service.pb.pb.cc -I /usr/local/protobuf/include/ -L /usr/local/protobuf/lib/ -lprotobuf -lprotoc -lprotobuf-lite -std=c++11
clean:
	rm service.pb.pb.*