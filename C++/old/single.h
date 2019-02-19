//
// Created by 贾凯超 on 2018/10/10.
// 用链表实现一个栈
// 思考：关于c++ 指针的应用
// new A 相当于 new A()
// 对于链表元素的查找是比较费时间的
//

#ifndef ENTER_SINGLE_H
#define ENTER_SINGLE_H

#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *next;
};

//单向链表
class single {
public:
    //创建一个链表
    Node *create() {
        Node *head = new Node;
        head->next = NULL;
        //头结点的data储存链表长度
        head->data = 0;
        return head;
    }

    //输出链表
    void echo(Node *head) {
        Node *current = head;
        int flag = 1;
        while (true) {
            if (flag == 1) {
                cout << "[" << current->data << "] ";
            } else {
                cout << current->data << " ";
                if (current->next == NULL) {
                    break;
                }
            }
            flag++;
            current = current->next;
        }
        cout << endl;
    }

    //向链表末尾添加一个数据
    bool push(Node *head, int param) {
        head->data += 1;
        Node *current = head;
        Node *last = new Node;
        last->data = param;
        last->next = NULL;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = last;
        return true;
    }

    //删除链表最后一个元素
    bool pop(Node *head) {
        Node *current = head;
        Node *pre;
        //如果链表长度小于等于0则直接返回头结点
        if (head->data <= 0) {
            return head;
        }
        while (current->next != NULL) {
            pre = current;
            current = current->next;
        }
        pre->next = NULL;
        delete current;
        return true;
    }
};


#endif //ENTER_SINGLE_H
