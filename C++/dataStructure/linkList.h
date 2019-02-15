//
// Created by 贾凯超 on 2019/2/14.
// 单链表
//

#ifndef STUDY_LINKLIST_H
#define STUDY_LINKLIST_H

#endif //STUDY_LINKLIST_H

#include <vector>
#include <iostream>

using namespace std;

class LinkNode {
public:
    LinkNode *next; //下一个节点
    LinkNode *pre; //前一个节点
    int data; //数据
};

class SingleLinkList {
public:
    LinkNode *head;
    LinkNode *current;
    int length;
    int currentLength;

    SingleLinkList(int length) {
        //声明一个哨兵节点
        LinkNode *preHead = new LinkNode();
        preHead->data = NULL;
        preHead->next = NULL;
        //头指针指向哨兵节点
        this->head = preHead;
        this->current = preHead;
        this->length = length;
        this->currentLength = 0;
    }

    //末尾增加一个数据
    bool addToLast(int data) {
        //链表当前长度大于总长度
        if (this->currentLength >= length) {
            cout << "链表已经存满数据" << endl;
            return false;
        }
        //申请一个节点
        LinkNode *temp = new LinkNode();
        temp->data = data;
        temp->next = NULL;
        //接入当前节点的下一个节点
        this->current->next = temp;
        //当前节点指到刚刚加入的节点
        this->current = this->current->next;
        this->currentLength ++;
        return true;
    }

    //删除最后一个
    bool deleteLast() {
        if (this->currentLength < 1) {
            cout << "链表已清空" << endl;
            return false;
        }
        LinkNode * temp = this->head->next;
        for (int i = 0; i < this->currentLength; i++) {
            //倒数第二个变成倒数第一个
            if (i == this->currentLength - 2) {
                this->current = temp;
            }
            //如果是最后一个则删除
            if (temp->next == NULL) {
                delete temp;
                this->current->next = NULL;
                break;
            }
            temp = temp->next;
        }
        this->currentLength --;
        return true;
    }
};
//双向链表
class DoubleLinkList {
public:
    LinkNode *head;
    LinkNode *current;
    int length;
    int currentLength;

    DoubleLinkList(int length) {
        //声明一个哨兵节点
        LinkNode *preHead = new LinkNode();
        LinkNode *nextEnd = new LinkNode();
        preHead->data = -1;
        preHead->next = NULL;
        preHead->pre = NULL;
        nextEnd->data = -1;
        nextEnd->next = NULL;
        nextEnd->pre = NULL;
        //头指针指向哨兵节点
        preHead->next = nextEnd;
        nextEnd->pre = preHead;
        this->head = preHead;
        this->current = preHead;
        this->length = length;
        this->currentLength = 0;
    }

    //末尾增加一个数据
    bool addToLast(int data) {
        //链表当前长度大于总长度
        if (this->currentLength >= length) {
            cout << "链表已经存满数据" << endl;
            return false;
        }
        //申请一个节点
        LinkNode *temp = new LinkNode();
        temp->data = data;
        temp->next = this->current->next;
        this->current->next->pre = temp;
        temp->pre = this->current;
        //接入当前节点的下一个节点
        this->current->next = temp;
        //当前节点指到刚刚加入的节点
        this->current = this->current->next;
        this->currentLength ++;
        return true;
    }

    //改变某一节点的位置
    bool addToPosition(LinkNode *insertNode, LinkNode *a) {
        //链表当前长度大于总长度
        if (this->currentLength >= length) {
            cout << "链表已经存满数据" << endl;
            return false;
        }
        insertNode->pre->next = insertNode->next;
        insertNode->next->pre = insertNode->pre;
        insertNode->next = a->next;
        a->next->pre = insertNode;
        insertNode->pre = a;
        //接入当前节点的下一个节点
        a->next = insertNode;
        return true;
    }

    //删除最后一个
    bool deleteLast() {
        if (this->currentLength < 1) {
            cout << "链表已清空" << endl;
            return false;
        }
        LinkNode *temp = this->head->next;
        for (int i = 0; i < this->currentLength; i++) {
            //倒数第二个变成倒数第一个
            if (i == this->currentLength - 2) {
                this->current->next->pre = temp;
                temp->next = this->current->next;
                this->current = temp;
            }
            //如果是最后一个则删除
            if (temp->next->data == -1) {
                delete temp;
                break;
            }
            temp = temp->next;
        }
        this->currentLength --;
        return true;
    }

    bool swapByPosition(int a, int b) {
        if (a > this->currentLength || b > this->currentLength) {
            return false;
        }
        LinkNode *La;
        LinkNode *Lb;
        LinkNode *temp = this->head->next;
        for (int i = 0; i < this->currentLength; i++) {
            if (i == a) {
                La = temp;
            }
            if (i == b) {
                Lb = temp;
            }
            temp = temp->next;
        }
        return swap(La, Lb);
    }

    //交换链表两个节点
    bool swap(LinkNode *a, LinkNode *b) {
        if (a->data == -1 || b->data == -1) {
            return false;
        }
        int temp = a->data;
        a->data = b->data;
        b->data = temp;
        return true;
    }

    //打印双向链表
    void printAll() {
        cout << "当前链表长度：" << this->currentLength << "/" << this->length << endl;
        LinkNode *temp = this->head->next;
        for (int i = 0; i < this->currentLength; i++) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};