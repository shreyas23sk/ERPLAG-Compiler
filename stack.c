// Group No 37
// Shreyas Kumar 2021A7PS2432P
// Prateek Kashyap 2021A7PS1449P
// Harshith Vasireddy 2021A7PS0504P
// Yuvraj Doshi 2021A7PS2425P

#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif

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

int isEmpty(StackPtr stack)
{
    return (stack->top == NULL);
}
