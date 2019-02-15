//
// 淘汰算法LRU
// Created by 贾凯超 on 2018/10/30.
//

#ifndef ENTER_LRU_H
#define ENTER_LRU_H

#endif //ENTER_LRU_H

#include <vector>
#include <iostream>
using namespace std;

class LRU {
private:
    vector<int> data;
    int max_size;
    int find(int a) {
        if (this->data.size() == 0) {
            return NULL;
        }
        for (int i = 0; i < this->data.size(); i++) {
            if (this->data[i] == a) {
                return i;
            }
        }
    }

public:
    LRU(int size) {
        this->data.resize(size);
        this->max_size = size;
    };
    //存储
    void save(int a) {
        int pos = find(a);
        //如果存在这个元素，将这个元素删除
        //否则检查队列是否已满
        //如果队列已满则删除队列头部
        //将新元素插入队尾
        if (pos) {
            vector<int>::iterator iter = this->data.begin() + pos;
            this->data.erase(iter);
        } else if (this->data.size() >= this->max_size) {
            vector<int>::iterator iter = this->data.begin();
            this->data.erase(iter);
        }
        this->data.push_back(a);
    }

    //获取最后一个元素
    int get() {
        return this->data[this->data.size()];
    }

    void print() {
        for (int i = 0; i < this->data.size(); i++) {
           cout << this->data[i] << " ";
        }
        cout << endl;
    }
};
