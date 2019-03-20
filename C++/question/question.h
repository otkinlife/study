//
// Created by 贾凯超 on 2018/10/31.
//

#ifndef ENTER_ARR_H
#define ENTER_ARR_H

using namespace std;

#include <vector>
#include <string>

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

    //查找第K大的元素
    //利用分之思想，将数组按主元划分为两部分，比主元大的放右边，比主元小的放左边
    //查看主元的后边有几个元素来判断大小
    int kLargeFind(vector<int> nums, int low, int high, int K) {
        if (K > high - low) {
            return 0;
        }
        int i = low;//i是最后一个小于主元的数的下标
        for (int j = low; j < high; j++)//遍历下标由low到high-1的数
        {
            if (nums[j] < nums[high])//如果数小于主元的话就将i向前挪动一个位置，并且交换j和i所分别指向的数
            {
                swap(nums[i], nums[j]);
                i++;
            }
        }
        //经历上面的循环之后下标为从low到i（包括i）的数就均为小于x的数了，现在将主元和i+1位置上面的数进行交换
        swap(nums[high], nums[i]);
        if (high - i == K - 1) {
            return nums[high];
        } else if (high - i > K - 1) {
            return kLargeFind(nums, i + 1, high, K);
        } else {
            return kLargeFind(nums, low, i - 1, K);
        }
    }

    //给定两个有序整数数组 nums1 和 nums2，将 nums2 合并到 nums1 中，使得 num1 成为一个有序数组。
    void merge(vector<int> nums1, int m, vector<int> nums2, int n) {
        for (int i = 0; i < n; i++) {
            nums1[m + i] = nums2[i];
        }
        for (int i = 0; i < m + n; i++) {
            for (int j = 0; j < m + n - i - 1; j++) {
                if (nums1[j] > nums1[j + 1]) {
                    swap(nums1[j + 1], nums1[j]);
                }
            }
        }
    }

    int lengthOfLastWord(string s) {
        int pos = s.rfind(" ");
        if (pos == -1) {
            return s.size();
        }
        if (pos == s.size() - 1) {
            return lengthOfLastWord(s.substr(0, pos));
        }
        return s.substr(pos + 1).size();
    }
};

#endif //ENTER_ARR_H
