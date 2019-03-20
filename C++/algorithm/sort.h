//
// Created by 贾凯超 on 2019/2/14.
//

#ifndef STUDY_SORT_H
#define STUDY_SORT_H

#endif //STUDY_SORT_H

#include <iostream>
#include "../dataStructure/linkList.h"

using namespace std;

/**
 * 该类主要实现了各种排序算法，基于双向链表实现
 *
 * 冒泡排序，插入排序，选择排序时间复杂度为O(n^2)。适合小规模数据排序
 *
 * 归并排序，快速排序时间复杂度为O(nlogn)。适合大规模数据排序
 */
static class Sort {
public:
    //冒泡排序
    //两两相互比较，交换位置
    //基于比较排序
    //空间复杂度O(1)，是原地排序
    //最好情况时间复杂度 O(n) 最坏情况时间复杂度 O(n^2) 平均情况时间复杂度 O(n^2)
    static DoubleLinkList *BubbleSort(DoubleLinkList *Link) {
        //每一次循环都找到最大或最小的数
        for (int i = 0; i < Link->currentLength; i++) {
            bool flag = false;
            LinkNode *temp = Link->head->next;
            //内部比较次数应该是 链表长度-外层循环完成次数-1
            for (int j = 0; j < Link->currentLength - 1 - i; j++) {
                if (temp->data > temp->next->data) {
                    Link->swap(temp, temp->next);
                    flag = true;
                }
                temp = temp->next;
            }
            //最好情况只需要一次循环
            if (!flag) {
                break;
            }
        }
        return Link;
    }

    //插入排序
    //线性表分为有序部分和无序部分，无序部分在有序部分查找正确位置并插入
    //基于比较排序
    //空间复杂度O(1)，是原地排序
    //最好情况时间复杂度 O(n) 最坏情况时间复杂度 O(n^2) 平均情况时间复杂度 O(n^2)
    static DoubleLinkList *InsertSort(DoubleLinkList *Link) {
        for (int i = 0; i < Link->currentLength - 1; i++) {
            LinkNode *sorted = Link->head->next;
            for (int m = 0; m < i; m++) {
                sorted = sorted->next;
            }
            LinkNode *temp = Link->head->next;
            for (int j = i; j > 0; j--) {
                if (sorted->next->data < temp->data) {
                    Link->addToPosition(sorted->next, temp->pre);
                    break;
                }
                temp = temp->next;
            }
        }
        return Link;
    }

    //选择排序
    //线性表从未排序部分找到最小值放到排序部分的最左边
    //基于比较排序
    //空间复杂度O(1)，是原地排序
    //最好情况时间复杂度 O(n^2) 最坏情况时间复杂度 O(n^2) 平均情况时间复杂度 O(n^2)
    static DoubleLinkList *SelectSort(DoubleLinkList *Link) {
        for (int i = 0; i < Link->currentLength - 1; i++) {
            LinkNode *unsorted = Link->head->next;
            for (int m = 0; m < i; m++) {
                unsorted = unsorted->next;
            }
            LinkNode *temp = unsorted;
            LinkNode *min = unsorted;
            for (int j = 0; j < Link->currentLength - i; j++) {
                if (temp->data < min->data) {
                    min = temp;
                }
                temp = temp->next;
            }
            Link->swap(unsorted, min);
        }
        return Link;
    }

    //todo: 归并排序

    //快速排序
    //选一个元素，比它大的放右边，比它小的放左边，递归调用
    //当数组low和high相等时表示只有一个元素无需排序，递归终止
    static void QuickSort(vector<int> &nums, int low, int high) {
        if (low >= high) {
            return;
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
        QuickSort(nums, low, i - 1);
        QuickSort(nums, i + 1, high);
    }
};