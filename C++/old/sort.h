#include <iostream>
#include <vector>
using namespace std;

class Sort {
public:
    /**
     * 冒泡排序
     * 时间复杂度O(n ^ 2)
     * 效能比较低，两个相邻元素分别比较，若满足条件再交换位置
     */
    vector<int> Bubble(vector<int> arr) {
        for (int i = 0; i < arr.size() - 1; i++) {
            for (int j = 0; j < arr.size() - i - 1; j++) {
                if (arr[j] < arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        return arr;
    }

    vector<int> Select(vector<int> arr) {
        for (int i = 0; i < arr.size(); i++) {
            for (int j = 0; j < arr.size() - i; j++) {

            }
        }
    }
};