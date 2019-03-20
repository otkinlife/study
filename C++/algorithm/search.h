//
// Created by 贾凯超 on 2019/2/20.
//

#ifndef STUDY_SEARCH_H
#define STUDY_SEARCH_H

#endif //STUDY_SEARCH_H

#include <iostream>
#include <vector>

using namespace std;

class Search {
public:
    //二分查找非递归实现
    int bSearch(vector<int> nums, int target) {
        int low = 0;
        int high = nums.size() - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (target == nums[mid]) {
                return mid;
            } else if (target > nums[mid]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }
    //二分查找递归实现
    int bSearchR(vector<int> nums, int target, int low, int high) {
        int mid = (low + high) / 2;
        if (low > high) {
            return -1;
        }
        if (target == nums[mid]) {
            return mid;
        } else if (target > nums[mid]) {
            return bSearchR(nums, target, mid + 1, high);
        } else {
            return bSearchR(nums, target, low, mid - 1);
        }
    }
};