//
// Created by 贾凯超 on 2019/2/18.
//

#ifndef C_LEETCODE_H
#define C_LEETCODE_H

#endif //C_LEETCODE_H

#include <iostream>
#include <vector>
#include <stack>
#include <string.h>
#include <set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
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

    //编写一个函数来查找字符串数组中的最长公共前缀。
    //如果不存在公共前缀，返回空字符串 ""。
    string longestCommonPrefix(vector<string> &strs) {
        //先找到最短长度的字符串
        //todo
    }

    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode *p;
        p = head;
        vector<ListNode *> temp;
        while (p != NULL) {
            temp.push_back(p);
            if (p->next == NULL) {
                break;
            }
            p = p->next;
        }
        //要删除的节点位置
        int i = temp.size() - n;
        //删除第一个节点
        if (i < 1) {
            if (temp[0]->next != NULL) {
                head = temp[1];
            } else {
                head = NULL;
            }
        } else if (i == temp.size() - 1) {
            temp[i - 1]->next = NULL;
        } else {
            temp[i - 1]->next = temp[i + 1];
        }
        return head;
    }

    //给定一个排序数组，你需要在原地删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。
    //不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。
    int removeDuplicates(vector<int> nums) {
        if (nums.size() < 1) return 0;
        int i = 1;
        while (i < nums.size()) {
            if (nums[i] == nums[i - 1]) {
                nums.erase(nums.begin() + i - 1);
            } else {
                i++;
            }
        }
        return i;
    }

    //给定一个数组 nums 和一个值 val，你需要原地移除所有数值等于 val 的元素，返回移除后数组的新长度。
    //不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。
    //元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
    int removeElement(vector<int> nums, int val) {
        if (nums.size() < 1) return 0;
        int i = 0;
        while (i < nums.size()) {
            if (nums[i] == val) {
                nums.erase(nums.begin() + i);
            } else {
                i++;
            }
        }
        return i;
    }

    vector<int> plusOne(vector<int> &digits) {
        long int nums = 0;
        for (int i = 0; i < digits.size(); i++) {
            nums = nums * 10 + digits[i];
        }
        nums++;
        digits.clear();
        stack<int> res;
        while (nums != 0) {
            int temp = nums % 10;
            res.push(temp);
            cout << res.top() << endl;
            nums /= 10;
        }
        while (!res.empty()) {
            cout << res.top() << endl;
            digits.push_back(res.top());
            res.pop();
        }
        for (int i = 0; i < digits.size(); i++) {
            cout << digits[i] << endl;
        }
        return digits;
    }

    //将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *p = l1;
        ListNode *q = l2;
        ListNode *res = new ListNode(0);
        ListNode *cur = res;
        while (p != NULL && q != NULL) {
            if (p->val < q->val) {
                cur->next = p;
                p = p->next;
            } else {
                cur->next = q;
                q = q->next;
            }
            cur = cur->next;
        }
        if (p == NULL) {
            cur->next = q;
        }
        if (q == NULL) {
            cur->next = p;
        }
        return res->next;
    }

    //合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        ListNode *temp = NULL;
        if (lists.size() <= 0) {
            return NULL;
        } else if (lists.size() == 1) {
            return lists[0];
        } else {
            temp = lists[0];
            for (int i = 1; i < lists.size(); i++) {
                temp = mergeTwoLists(temp, lists[i]);
            }
        }
        return temp;
    }

    //给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
    //请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
    double findMedianSortedArrays(vector<int> nums1, vector<int> nums2) {
        vector<int> temp;
        int i = 0;
        int j = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] < nums2[j]) {
                temp.push_back(nums1[i]);
                i++;
            } else {
                temp.push_back(nums2[j]);
                j++;
            }
        }
        for (; i < nums1.size(); i++) {
            temp.push_back(nums1[i]);
        }
        for (; j < nums2.size(); j++) {
            temp.push_back(nums2[j]);
        }
        double res = 0.0;
        int flag = temp.size() % 2;
        int mid = temp.size() / 2;
        if (flag == 1) {
            res = temp[mid];
        } else {
            res = (temp[mid] + temp[mid - 1]) / 2.0;
        }
        return res;
    }

    //给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
    //candidates 中的数字可以无限制重复被选取。
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> res;
        vector<int> item;
        backtrade(candidates, 0, target, item, res);
        return res;

    }

    void backtrade(vector<int> candidates, int start, int target, vector<int> item, vector<vector<int>> &res) {
        if (target < 0)
            return;
        if (target == 0) {
            res.push_back(item);
            return;
        }
        for (int i = start; i < candidates.size(); i++) {
            item.push_back(candidates[i]);
            backtrade(candidates, i, target - candidates[i], item, res);
            item.pop_back();
        }
    }


    bool isSameTree(TreeNode *p, TreeNode *q) {
        if (p == NULL && q == NULL) {
            return true;
        } else if ((p == NULL && q != NULL) || (p != NULL && q == NULL)) {
            return false;
        } else if (p != NULL && q != NULL) {
            if (p->val == q->val) {
                if (p->left == NULL && q->left == NULL && p->right == NULL && q->right == NULL) {
                    return true;
                }
            } else {
                return false;
            }
        }
        bool leftRes = false;
        bool rightRes = false;
        leftRes = isSameTree(p->left, q->left);
        rightRes = isSameTree(p->right, q->right);
        return leftRes && rightRes;
    }

    string addBinary(string a, string b) {
        int length = 0;
        string res;
        if (a.size() > b.size()) {
            length = a.size();
            while (b.size() < length) {
                b.insert(0, "0");
            }
        } else {
            length = b.size();
            while (a.size() < length) {
                a.insert(0, "0");
            }
        }
        int flag = 0;
        for (int i = length - 1; i >= 0; i--) {
            int ta = a[i] == '1' ? 1 : 0;
            int tb = b[i] == '1' ? 1 : 0;
            int temp = ta + tb + flag;
            if (temp == 2) {
                flag = 1;
                res.insert(0, "0");
                if (i == 0) {
                    res.insert(0, "1");
                }
            } else if (temp == 3) {
                flag = 1;
                res.insert(0, "1");
                if (i == 0) {
                    res.insert(0, "1");
                }
            } else if (temp == 1) {
                flag = 0;
                res.insert(0, "1");
            } else {
                flag = 0;
                res.insert(0, "0");
            }
        }
        return res;
    }

    //假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
    //每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
    int climbStairs(int n) {
        if (n == 1) {
            return 1;
        }
        if (n == 2) {
            return 2;
        }
        return climbStairs(n - 1) + climbStairs(n - 2);
    }

    //杨辉三角
    /* 输入: 5
     输出:
     [
         [1],
        [1,1],
       [1,2,1],
      [1,3,3,1],
     [1,4,6,4,1]
     ]*/
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        if (numRows <= 0) {
            return res;
        }
        for (int i = 0; i < numRows; i++) {
            vector<int> temp;
            if (i == 0) {
                temp.push_back(1);
            } else if (i == 1) {
                temp.push_back(1);
                temp.push_back(1);
            } else {
                temp.push_back(1);
                for (int j = 1; j < i; j++) {
                    temp.push_back(res[i - 1][j - 1] + res[i - 1][j]);
                }
                temp.push_back(1);
            }
            res.push_back(temp);
        }
        return res;
    }
};
