#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif


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
