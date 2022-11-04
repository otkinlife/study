// Package files 该包用于文件处理
// catch_log主要实现了日志抓取能力
// 该文件会维护一个全局的"打开日志文件列表"，在调用NewAgentLogFileClient方法时会向该列表中加入一个打开文件
// "打开日志文件列表"中的文件会被定时清理
// "打开日志文件列表"中维护了每个日志文件的行的偏移量索引方便定位到具体的行
// "打开日志文件列表"的文件偏移量索引在每次事件触发时进行更新

package files

import (
	"bufio"
	"errors"
	"io"
	"os"
	"strconv"
	"strings"
	"time"
)

type ReadMode int32

const (
	ReadMode_ALL  ReadMode = 0 // 读取全文件
	ReadMode_SUB  ReadMode = 1 // 读取某几行
	ReadMode_HEAD ReadMode = 2 // 读取前几行
	ReadMode_TAIL ReadMode = 3 // 读取后几行
	ReadMode_LAST ReadMode = 4 // 从第几行读到最后
)

type File struct {
	Name       string `protobuf:"bytes,1,opt,name=name,proto3" json:"name,omitempty"`
	Size       int64  `protobuf:"varint,2,opt,name=size,proto3" json:"size,omitempty"`
	UpdateTime string `protobuf:"bytes,3,opt,name=update_time,json=updateTime,proto3" json:"update_time,omitempty"`
	NextLine   int64  `protobuf:"varint,4,opt,name=next_line,json=nextLine,proto3" json:"next_line,omitempty"`
}

type ModeExtra struct {
	Start int64 // 开始行号
	End   int64 // 结束行号
	Head  int64 // 取开始的行数
	Tail  int64 // 取结尾的行数
	Last  int64 // 倒数第n行
}

type AgentLogFile struct {
	File           *os.File
	LogPath        string
	Count          int64
	LastModifyTime int64
	LastOffset     int64
	OffsetIndex    map[int64]int64
	ReadTime       int64
	NextLine       int64
}

// 维护一个打开文件列表，对于已经扫描过的文件进行目录缓存
var openFileList = map[string]*AgentLogFile{}

func NewAgentLogFileClient(logPath string) (*AgentLogFile, error) {
	// 如果该文件已经在打开文件列表中存在则直接返回
	if v, ok := openFileList[logPath]; ok {
		return v, nil
	}

	// 初始化文件描述符
	f, err := os.OpenFile(logPath, os.O_RDONLY, 0666)
	if err != nil {
		return nil, err
	}

	a := &AgentLogFile{
		File:           f,
		LogPath:        logPath,
		LastOffset:     0,
		OffsetIndex:    map[int64]int64{},
		Count:          0,
		LastModifyTime: 0,
		ReadTime:       time.Now().Unix(),
	}
	openFileList[logPath] = a
	return a, nil
}

// GetMeta 获取文件的元信息
func (a *AgentLogFile) GetMeta() *File {
	meta, _ := a.File.Stat()
	return &File{
		Name:       meta.Name(),
		Size:       meta.Size(),
		UpdateTime: meta.ModTime().Format("2006-01-02 15:04:05"),
		NextLine:   a.NextLine,
	}
}

// Read 读取的文件内容
// mode是模式，0表示读全部，1表示读n到m行，2表示读前n行，3表示读后n行，4表示从第n行读到最后
// extra是mode的额外参数，负责为不同的mode提供条件
// 该方法返回一个倒序排列的list指针，每一项代表一行
func (a *AgentLogFile) Read(mode int, extra *ModeExtra) (*[]string, error) {
	rows := &[]string{} // 存取所有内容
	var err error

	//刷新offsets索引
	a.freshOffsets()
	a.ReadTime = time.Now().Unix()
	// 取文件
	switch mode {
	case int(ReadMode_ALL):
		rows, err = a.getRows(1, a.Count)
	case int(ReadMode_SUB):
		rows, err = a.getRows(extra.Start, extra.End)
	case int(ReadMode_HEAD):
		end := extra.Start + extra.Head - 1
		if end > a.Count {
			end = a.Count
		}
		rows, err = a.getRows(1, end)
	case int(ReadMode_TAIL):
		start := a.Count - extra.Tail + 1
		if start < 1 {
			start = 1
		}
		rows, err = a.getRows(start, a.Count)
	case int(ReadMode_LAST):
		rows, err = a.getRows(extra.Last, a.Count)
	default:
		rows, err = a.getRows(1, a.Count)
	}
	return rows, err
}

// 扫描文件，建立偏移量目录
func (a *AgentLogFile) freshOffsets() {
	meta, _ := a.File.Stat()

	//上一次处理的数据
	line := a.Count
	offset := a.LastOffset

	// offset指针指向最后一行的位置
	_, _ = a.File.Seek(a.LastOffset, io.SeekStart)
	reader := bufio.NewReader(a.File)
	for offset < meta.Size() {
		//处理第一行
		if line == 0 {
			line += 1
			a.OffsetIndex[line] = 0
		} else {
			catch, err := reader.ReadBytes('\n')
			//处理最后一行
			if err == io.EOF {
				return
			}
			//获取下一行的偏移量
			offset += int64(len(catch))
			line += 1
			a.OffsetIndex[line] = offset
			a.LastOffset = offset
		}
		a.Count = line
	}
}

func (a *AgentLogFile) getRows(start int64, end int64) (*[]string, error) {
	var startOffset int64 = 0
	var endOffset int64 = 0
	if v, ok := a.OffsetIndex[start]; ok {
		startOffset = v
	}
	if v, ok := a.OffsetIndex[end+1]; ok {
		endOffset = v - 1
	} else {
		meta, _ := a.File.Stat()
		endOffset = meta.Size()
	}

	//条件校验
	if startOffset > endOffset {
		return nil, errors.New("get offset error")
	}
	if startOffset == endOffset {
		return &[]string{}, nil
	}
	// 读取文件
	contentSize := endOffset - startOffset
	rowsBytes := make([]byte, contentSize)
	_, _ = a.File.ReadAt(rowsBytes, startOffset)

	var resp []string
	rows := strings.Split(string(rowsBytes), "\n")
	if len(rows) != int(end-start)+1 {
		return nil, errors.New("count no matched")
	}
	current := start
	for _, v := range rows {
		if v == "" {
			continue
		}
		row := strconv.Itoa(int(current)) + "(^_^)" + v
		resp = append(resp, row)
		current += 1
	}
	a.NextLine = current
	reverse(&resp)
	return &resp, nil
}

func reverse(arr *[]string) {
	var temp string
	length := len(*arr)
	for i := 0; i < length/2; i++ {
		temp = (*arr)[i]
		(*arr)[i] = (*arr)[length-1-i]
		(*arr)[length-1-i] = temp
	}
}

// CleanOpenFileList 清理全局的打开文件列表
// 该方法将清理最后读取时间在1小时以上的文件描述符，并将该描述符从全局文件列表中删除
func CleanOpenFileList() {
	if len(openFileList) == 0 {
		return
	}
	for _, o := range openFileList {
		if time.Now().Unix()-o.ReadTime > 3600 {
			if err := o.File.Close(); err == nil {
				delete(openFileList, o.LogPath)
				o = nil
			}
		}
	}
}
