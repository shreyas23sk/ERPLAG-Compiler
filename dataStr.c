#include "parserDef.h"

// Linked List Functions

LinkedListPtr createLinkedList()
{
    LinkedListPtr newList = (LinkedListPtr)malloc(sizeof(LinkedList));
    if (newList != NULL)
    {
        newList->head = NULL;
        newList->tail = NULL;
    }
    return newList;
}

NodePtr createNode(SYM newData)
{
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
    if (newNode != NULL)
    {
        newNode->data = newData;
        newNode->next = NULL;
        newNode->prev = NULL;
    }
    return newNode;
}

void insertNode(LinkedListPtr list, SYM newData)
{
    NodePtr newNode = createNode(newData);
    if (newNode != NULL)
    {
        if (list->head == NULL)
        {
            list->head = newNode;
        }
        else
        {
            NodePtr current = list->head;
            while (current->next != NULL)
                current = current->next;
            current->next = newNode;
            newNode->prev = current;
        }
        list->tail = newNode;
    }
}

void printList(LinkedListPtr list)
{
    if (list == NULL || list->head == NULL)
    {
        printf("Empty List\n");
        return;
    }
    NodePtr curr = list->head;
    while (curr != NULL)
    {
        if (curr->data.type == TERM)
            printf("%s ", tokenToString(curr->data.tk));
        else
            printf("%s ", NTtoString(curr->data.nt));
        curr = curr->next;
    }
    printf("\n");
}

// Stack Functions

StackPtr createStack()
{
    StackPtr stack = (StackPtr)malloc(sizeof(Stack));
    if (stack != NULL)
    {
        stack->top = NULL;
        stack->tail = NULL;
    }
    return stack;
}

void push(StackPtr stack, ParseNodePtr node)
{
    if (stack != NULL && node != NULL)
    {
        ParseNodeLLPtr newNode = (ParseNodeLLPtr)malloc(sizeof(ParseNodeLL));
        if (newNode != NULL)
        {
            newNode->val = node;
            newNode->next = stack->top;
            if (stack->top != NULL)
                stack->top->prev = newNode;
            else
                stack->tail = newNode;
            newNode->prev = NULL;
            stack->top = newNode;
        }
    }
}

ParseNodePtr pop(StackPtr stack)
{
    if (stack == NULL || stack->top == NULL)
        return NULL;
    ParseNodeLLPtr temp = stack->top;
    stack->top = temp->next;
    if (stack->top != NULL)
        stack->top->prev = NULL;
    else
        stack->tail = NULL;
    ParseNodePtr poppedValue = temp->val;
    free(temp);
    return poppedValue;
}

ParseNodePtr peek(StackPtr stack)
{
    if (stack != NULL && stack->top != NULL)
        return stack->top->val;
    return NULL;
}

int isStackEmpty(StackPtr stack)
{
    return (stack == NULL || stack->top == NULL);
}

// Parse Tree Functions

ParseTreePtr createParseTree()
{
    ParseTreePtr newTree = (ParseTreePtr)malloc(sizeof(ParseTree));
    if (newTree != NULL)
        newTree->root = NULL;
    return newTree;
}

ParseNodePtr createParseNode(SYM value)
{
    ParseNodePtr newNode = (ParseNodePtr)malloc(sizeof(ParseNode));
    if (newNode != NULL)
    {
        newNode->val = value;
        newNode->children = NULL;
        newNode->noOfChildren = 0;
    }
    return newNode;
}

void addChild(ParseNodePtr parent, ParseNodePtr child)
{
    if (parent != NULL && child != NULL)
    {
        parent->noOfChildren++;
        parent->children = (ParseNodePtr *)realloc(parent->children, parent->noOfChildren * sizeof(ParseNodePtr));
        if (parent->children != NULL)
            parent->children[parent->noOfChildren - 1] = child;
    }
}

void printParseTreeHelper(ParseNodePtr node, int depth)
{
    if (node == NULL)
        return;
    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("%c\n", node->val);
    for (int i = 0; i < node->noOfChildren; i++)
        printParseTreeHelper(node->children[i], depth + 1);
}

void printParseTree(ParseTreePtr tree)
{
    if (tree == NULL || tree->root == NULL)
    {
        printf("Empty Tree\n");
        return;
    }
    printParseTreeHelper(tree->root, 0);
}
