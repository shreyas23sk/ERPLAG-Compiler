#ifndef PARSERNONTERM
#define PARSERNONTERM
#include "parserNonTerm.h"
#endif
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    SYM data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

typedef Node* NodePtr;
typedef LinkedList* LinkedListPtr;

LinkedListPtr createLinkedList();
NodePtr createNode(SYM newData);
void insertNode(LinkedListPtr list, SYM newData);

// unnecessary as of now

// void deleteNode(LinkedListPtr list, SYM dataToDelete);
// void displayList(LinkedList list);

#endif