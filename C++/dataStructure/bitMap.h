//
// Created by 贾凯超 on 2019/4/1.
//

#ifndef STUDY_BITMAP_H
#define STUDY_BITMAP_H

#endif //STUDY_BITMAP_H

#include <math.h>

using namespace std;

class bitMap {
private:
    unsigned int *map = 0;
    int size = 0;
public:
    bitMap(int size);

    bool setMap(int position, int val);

    int getMap(int position);

    void print();
};

//构造函数
bitMap::bitMap(int size) {
    this->size = size;
    //求出需要几个int型
    int nums = ceil(size / 32.0);
    //申请数组并且初始化
    this->map = new uint[nums];
    for (int i = 0; i < nums; i++) {
        this->map[i] = 0;
    }
}

//设置位值
bool bitMap::setMap(int position, int val) {
    int index = position / 32;
    int num = position % 32;
    if (val == 1) {
        this->map[index] |= (1 << (32 - num));
    } else if (val == 0) {
        this->map[index] &= (0 << (32 - num));
    } else {
        return false;
    }
    return true;
}

//获取某一位图
int bitMap::getMap(int position) {
    int index = position / 32;
    int num = position % 32;
    int temp = this->map[index] >> (32 - num);
    return temp % 2;
}

//打印位图
void bitMap::print() {
    for (int i = 0; i < this->size; i++) {
        int temp = this->getMap(i);
        cout << "[" << i << "]: " << temp << endl;
    }
}
