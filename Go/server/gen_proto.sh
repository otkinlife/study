#!/bin/bash
#生成go的协议结构体
#该命令要求执行环境安装protoc
#参考文档：https://developers.google.com/protocol-buffers/docs/reference/go-generated#package
#http网关参考文档：https://github.com/grpc-ecosystem/grpc-gateway#usage

#定义proto文件所在的目录：用于protoc命令读取
PROTO_DIR=/Users/kcjia/Developer/study/Go/server/proto

#删除之前生成的proto文件
rm -rf $PROTO_DIR/event_handler

# 使用protoc生成文件
# -I 参数要包含所有需要读取文件的目录
# out 是输出的文件目录
protoc -I=$GOPATH/src -I=$PROTO_DIR \
--go_out=$PROTO_DIR \
--go-grpc_out=$PROTO_DIR \
--grpc-gateway_out=$PROTO_DIR \
$PROTO_DIR/*.proto