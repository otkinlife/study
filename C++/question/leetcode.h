//
// Created by 贾凯超 on 2019/2/18.
//

#ifndef C_LEETCODE_H
#define C_LEETCODE_H

#endif //C_LEETCODE_H

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class LeetCode {
public:
    //给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
    //你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
    vector<int> twoSum(vector<int> &nums, int target) {
        vector<int> res = {};
        for (int i = 0; i < nums.size() - 1; i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    res = {i, j};
                    break;
                }
            }
        }
        return res;
    }

    //给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
    //如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
    //您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *current;
        ListNode *head;
        int i = 1;
        int flag = 0;
        while (l1 != NULL || l2 != NULL || flag == 1) {
            int l1data;
            int l2data;
            l1data = l1 == NULL ? 0 : l1->val;
            l2data = l2 == NULL ? 0 : l2->val;
            int sum = l1data + l2data;
            //处理进位
            if (flag == 1) {
                sum += 1;
            }
            if (sum >= 10) {
                sum = sum % 10;
                flag = 1;
            } else {
                flag = 0;
            }
            ListNode *temp = new ListNode(sum);
            l1 = l1 == NULL ? NULL : l1->next;
            l2 = l2 == NULL ? NULL : l2->next;
            if (i == 1) {
                head = current = temp;
            } else {
                current->next = temp;
                current = current->next;
            }
            i++;
        }
        return head;
    }

    //给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
    int lengthOfLongestSubstring(string s) {
        set<char> cache;
        int maxlen = 0;
        int left = 0;
        int index = 0;
        while (index < s.size()) {
            if (cache.find(s[index]) == cache.end()) {
                cache.insert(s[index++]);
                maxlen = max(maxlen, (int) cache.size());
            } else {
                cache.erase(s[left++]);
            }
        }
        return maxlen;
    }

    //给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
    //请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
    //你可以假设 nums1 和 nums2 不会同时为空。
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
        vector<int> merge;
    }

    int reverse(int x) {
        int res = 0;
        while (x != 0) {
            int temp = x % 10;
            x = x / 10;
            //8位整形溢出判断
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && temp > 7)) return 0;
            if (res < INT_MIN / 10 || (res == INT_MIN / 10 && temp < -8)) return 0;
            res = res * 10 + temp;
        }
        return res;
    }
    //判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
    bool isPalindrome(int x) {
        if (x < 0) return false;
        int res = 0;
        int old = x;
        while (x != 0) {
            int temp = x % 10;
            x = x / 10;
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && temp > 7)) return 0;
            if (res < INT_MIN / 10 || (res == INT_MIN / 10 && temp < -8)) return 0;
            res = res * 10 + temp;
        }
        if (res == old) {
            return true;
        }
        return false;
    }
}
