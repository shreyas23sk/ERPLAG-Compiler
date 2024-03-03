#include "parserDef.h"

LinkedListPtr createLinkedList()
{
    LinkedListPtr newList = (LinkedListPtr)malloc(sizeof(LinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}

NodePtr createNode(SYM newData)
{
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertNode(LinkedListPtr list, SYM newData)
{
    NodePtr newNode = createNode(newData);

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

void printList(LinkedListPtr list)
{
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

StackPtr createStack()
{
    StackPtr stack = (StackPtr)malloc(sizeof(Stack));
    stack->top = NULL;
    stack->tail = NULL;
    return stack;
}

void push(StackPtr stack, ParseNodePtr node)
{
    ParseNodeLLPtr newNode = (ParseNodeLLPtr)malloc(sizeof(ParseNodeLL));
    newNode->val = node;

    if (stack->top == NULL)
    {
        stack->top = newNode;
        stack->tail = newNode;
        newNode->prev = NULL;
        newNode->next = NULL;
    }
    else
    {
        newNode->next = stack->top;
        stack->top->prev = newNode;
        stack->top = newNode;
    }
}

ParseNodePtr pop(StackPtr stack)
{
    if (stack->top == NULL)
    {
        return NULL;
    }

    ParseNodeLLPtr temp = stack->top;

    if (stack->top == stack->tail)
    {
        stack->top = NULL;
        stack->tail = NULL;
    }
    else
    {
        stack->top = stack->top->next;
        stack->top->prev = NULL;
    }

    temp->next = NULL;

    return temp->val;
}

ParseNodePtr peek(StackPtr stack)
{
    return stack->top->val;
}

int isStackEmpty(StackPtr stack)
{
    return (stack->top == NULL);
}

ParseTreePtr createParseTree()
{
    ParseTreePtr newTree = (ParseTreePtr)malloc(sizeof(ParseTree));
    newTree->root = NULL;
    return newTree;
}

ParseNodePtr createParseNode(SYM value)
{
    ParseNodePtr newNode = (ParseNodePtr)malloc(sizeof(ParseNode));
    newNode->val = value;
    newNode->children = NULL;
    newNode->noOfChildren = 0;
    return newNode;
}

void addChild(ParseNodePtr parent, ParseNodePtr child)
{
    parent->noOfChildren++;
    parent->children = (ParseNodePtr *)realloc(parent->children, parent->noOfChildren * sizeof(ParseNodePtr));
    parent->children[parent->noOfChildren - 1] = child;
}

void printParseTreeHelper(ParseNodePtr node, int depth)
{
    if (node == NULL)
    {
        return;
    }

    for (int i = 0; i < depth; i++)
    {
        printf("  "); // Print spaces for indentation
    }

    printf("%c\n", node->val); // Print the node's value

    for (int i = 0; i < node->noOfChildren; i++)
    {
        printParseTreeHelper(node->children[i], depth + 1); // Recursively print children
    }
}

void printParseTree(ParseTreePtr tree)
{
    if (tree == NULL || tree->root == NULL)
    {
        printf("Empty Tree\n");
        return;
    }

    printParseTreeHelper(tree->root, 0); // Start printing from the root with depth 0
}
