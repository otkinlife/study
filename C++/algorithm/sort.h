//
// Created by 贾凯超 on 2019/2/14.
//

#ifndef STUDY_SORT_H
#define STUDY_SORT_H

#endif //STUDY_SORT_H

#include <iostream>
#include "../dataStructure/linkList.h"
using namespace std;

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
                if(temp->data > temp->next->data) {
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
                if(sorted->next->data < temp->data) {
                    Link->addToPosition(sorted->next, temp->pre);
                    break;
                }
                temp = temp->next;
            }
        }
        return Link;
    }
};