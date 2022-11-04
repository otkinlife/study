// Package server GrpcServer的是实现方式：GrpcServer和GrpcHTTPGateway监听同一个端口
// grpc http gateway 的原理是请求过来之后打到http gateway的端口，在有gateway端口将请求转发到grpc server 的端口上
// 虽然本文件的代码将两个端口合并为一个端口，但是链路上没有简化。一个http请求过来之后判断是grpc请求还是普通web请求。
// 如果是普通web请求还是要走一次转发
package server

import (
	"context"
	"fmt"
	"github.com/grpc-ecosystem/grpc-gateway/runtime"
	"golang.org/x/net/http2"
	"golang.org/x/net/http2/h2c"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"google.golang.org/grpc/reflection"
	"kcjia/server/proto/Go/server/proto/proto_demo"
	"net/http"
	"strings"
)

var HsHandle *http.Server
var BaseServer proto_demo.DemoServer

func main() {
	runServer()
}

func runServer() bool {
	//grpcServer
	grpcServer := runGrpcServer()

	//httpServer
	httpServer := runHttpServer()
	gatewayMux := runGatewayServer()
	httpServer.Handle("/", gatewayMux)

	//监听端口
	port := "8080"
	fmt.Println("agent started with port:", port, "...")
	HsHandle = &http.Server{Addr: ":" + port, Handler: grpcHandlerFunc(grpcServer, httpServer)}
	err := HsHandle.ListenAndServe()
	if err != nil && err != http.ErrServerClosed {
		fmt.Printf("server start failed: %s\n", err)
		return false
	}
	return true
}

func runGrpcServer() *grpc.Server {
	s := grpc.NewServer()
	proto_demo.RegisterDemoServer(s, BaseServer)
	reflection.Register(s)
	return s
}

func runHttpServer() *http.ServeMux {
	s := http.NewServeMux()
	return s
}

func runGatewayServer() *runtime.ServeMux {
	endpoint := ":" + "8080"
	gwMux := runtime.NewServeMux()
	options := []grpc.DialOption{grpc.WithTransportCredentials(insecure.NewCredentials())}
	err := proto_demo.RegisterDemoHandlerFromEndpoint(context.Background(), gwMux, endpoint, options)
	if err != nil {
		fmt.Println(err)
	}
	return gwMux
}

func grpcHandlerFunc(grpcServer *grpc.Server, httpHandler http.Handler) http.Handler {
	return h2c.NewHandler(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		// 跨域问题解决
		w.Header().Set("Access-Control-Allow-Origin", "*")
		// 转发协议
		if r.ProtoMajor == 2 && strings.HasPrefix(r.Header.Get("Content-Type"), "application/grpc") {
			grpcServer.ServeHTTP(w, r)
		} else {
			httpHandler.ServeHTTP(w, r)
		}
	}), &http2.Server{})
}
