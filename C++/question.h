//
// Created by 贾凯超 on 2018/10/31.
//

#ifndef ENTER_ARR_H
#define ENTER_ARR_H

using namespace std;
#include <vector>

class Question {
private:
public:
    //输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
    //使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分，
    //并保证奇数和奇数，偶数和偶数之间的相对位置不变。
    void reOrderArray(vector<int> &array) {
        vector<int> temp;
        for (int i = 0; i < array.size(); i++) {
            if (array[i] % 2 == 1) {
                temp.push_back(array[i]);
            }
        }
        for (int i = 0; i < array.size(); i++) {
            if (array[i] % 2 == 0) {
                temp.push_back(array[i]);
            }
        }
        array.empty();
        array = temp;
    }
};

#endif //ENTER_ARR_H
