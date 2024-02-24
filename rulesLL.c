#ifndef RULESLL_H
#define RULESLL_H
#include "rulesLL.h"
#endif 

LinkedListPtr createLinkedList() {
    LinkedListPtr newList = (LinkedListPtr)malloc(sizeof(LinkedList));
    newList->head = NULL;
    return newList;
}

NodePtr createNode(SYM newData) {
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;
    return newNode;
}

void insertNode(LinkedListPtr list, SYM newData) {
    NodePtr newNode = createNode(newData);

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        NodePtr current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
