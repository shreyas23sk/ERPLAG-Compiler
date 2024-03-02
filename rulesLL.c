#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif

LinkedListPtr createLinkedList() {
    LinkedListPtr newList = (LinkedListPtr)malloc(sizeof(LinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}

NodePtr createNode(SYM newData) {
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;
    newNode->prev = NULL;
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
        newNode->prev = current;
    }

    list->tail = newNode;
}

StackPtr createStack() {
    StackPtr newStack = (StackPtr)malloc(sizeof(Stack));
    newStack->ll = createLinkedList();
    return newStack;
}

void push(StackPtr stack, SYM newData) {
    insertNode(stack->ll, newData);
}

int isStackEmpty(StackPtr stack) {
    return (stack->ll->head == NULL);
}

SYM pop(StackPtr stack) {
    Node* nodeToPop = stack->ll->tail;
    SYM data = nodeToPop->data;
        
    // Update tail of the linked list
    stack->ll->tail = nodeToPop->prev;
        
    // Check if the popped node was the only node in the list
    if (stack->ll->tail != NULL) {
        stack->ll->tail->next = NULL;
    } else {
        // If there was only one node, update head as well
        stack->ll->head = NULL;
    }
        
    free(nodeToPop); // Free memory of the popped node
    return data;
}

SYM peek(StackPtr stack) {
    return stack->ll->tail->data;
}

ParseTreePtr createParseTree() {
    ParseTreePtr newTree = (ParseTreePtr)malloc(sizeof(ParseTree));
    newTree->root = NULL;
    return newTree;
}

ParseNodePtr createParseNode(SYM value) {
    ParseNodePtr newNode = (ParseNodePtr)malloc(sizeof(ParseNode));
    newNode->val = value;
    newNode->children = NULL;
    newNode->noOfChildren = 0;
    return newNode;
}

void addChild(ParseNodePtr parent, SYM value) {
    ParseNodePtr child = createParseNode(value);
    parent->noOfChildren++;
    parent->children = (ParseNodePtr*)realloc(parent->children, parent->noOfChildren * sizeof(ParseNodePtr));
    parent->children[parent->noOfChildren - 1] = child;
}

void printParseTreeHelper(ParseNodePtr node, int depth) {
    if (node == NULL) {
        return;
    }
    
    for (int i = 0; i < depth; i++) {
        printf("  "); // Print spaces for indentation
    }
    
    printf("%c\n", node->val); // Print the node's value
    
    for (int i = 0; i < node->noOfChildren; i++) {
        printParseTreeHelper(node->children[i], depth + 1); // Recursively print children
    }
}

void printParseTree(ParseTreePtr tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("Empty Tree\n");
        return;
    }
    
    printParseTreeHelper(tree->root, 0); // Start printing from the root with depth 0
}
