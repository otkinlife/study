package server

import (
	"fmt"
	"net/http"
	"os"
	"time"
)

//op1: 使用default的Mux注册
func op1() {
	http.HandleFunc("/hello", hello)
	err := http.ListenAndServe(":8999", nil)
	if err != nil {
		os.Exit(1)
	}
}

//使用自定义mux注册
func op2() {
	//事实上
	mux := http.NewServeMux()
	//后端接口注册
	mux.HandleFunc("/hello", hello)

	//静态文件服务器注册
	mux.Handle("/", http.StripPrefix("/", http.FileServer(http.Dir("../client"))))
	fmt.Println("server start at port 8999")
	err := http.ListenAndServe(":8999", mux)
	if err != nil {
		os.Exit(1)
	}
}

//方式3： 使用自定义的handler
// 事实上handler是一个抽象，代码表了一次请求来之后的处理方式
// 方式1中使用了defaultMux，方式2中使用了自定义mux。Mux结构是handler的实现
// 除了mux之外常见的handler还有 http.FileServer http.StripPrefix http.TimeoutHandler 等
func op3() {
	handler := customHandler{}
	//使用超时handler
	th := http.TimeoutHandler(&handler, 3*time.Second, "超时了")
	http.Handle("/hello", th)
	http.ListenAndServe(":8080", nil)
}

type customHandler struct {
}

func (c *customHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {

}

func hello(w http.ResponseWriter, r *http.Request) {
	w.Write([]byte("hello"))
}
