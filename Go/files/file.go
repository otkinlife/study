package files

import (
	"fmt"
	"os"
)

// Status 获取文件状态
// os.Stat 方法返回了FileInfo对象
func Status(path string) {
	fileInfo, err := os.Stat(path)
	if err != nil {
		return
	}
	name := fileInfo.Name()       //文件名
	size := fileInfo.Size()       //文件大小
	isDir := fileInfo.IsDir()     //文件是否目录类型
	mode := fileInfo.Mode()       //文件权限
	modTime := fileInfo.ModTime() //文件修改时间
	sys := fileInfo.Sys()         //底层数据源：这里包括文件的UID和GID以及所有文件系统的信息
	fmt.Println(name, size, isDir, mode, modTime, sys)
}
