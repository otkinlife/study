#include <iostream>
#include "algorithm/sort.h"
using namespace std;

int main() {
    DoubleLinkList *LinkList = new DoubleLinkList(10);
    LinkList->addToLast(2);
    LinkList->addToLast(513);
    LinkList->addToLast(23);
    LinkList->swapByPosition(1,2);
    LinkList->addToLast(53);
    LinkList->addToLast(1);
    LinkList->addToLast(87);
    LinkList->addToLast(66);
    LinkList->printAll();
    //LinkList = Sort::BubbleSort(LinkList);
    //LinkList = Sort::InsertSort(LinkList);
    LinkList = Sort::SelectSort(LinkList);
    LinkList->printAll();
    return 0;
}