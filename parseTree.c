#include "parserDef.h"

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
