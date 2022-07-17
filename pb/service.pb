syntax = "proto2";
package rpc;

option cc_generic_services = true;

message rpcRequest{
    required int32 head = 1;
    required bytes msg = 2;
}

message rpcResponce {
    required bytes msg = 1;
}

//  /usr/local/protobuf/bin/protoc --cpp_out=./ service.pb 