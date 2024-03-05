#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif

ParseTreePtr createParseTree()
{
    ParseTreePtr newTree = (ParseTreePtr)malloc(sizeof(ParseTree));

    if (newTree != NULL)
        newTree->root = NULL;

    return newTree;
}

ParseNodePtr createParseNode(SYM value, int lineNo, char* lex)
{
    ParseNodePtr newNode = (ParseNodePtr)malloc(sizeof(ParseNode));


    if (newNode != NULL)
    {
        newNode->val = value;
        newNode->lex = lex;
        newNode->lineNo = lineNo;
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

        parent->children[parent->noOfChildren - 1] = child;
    }
}

void printParseNode(ParseNodePtr node, ParseNodePtr parent, FILE* fp)
{
    SYM s = node->val;
    if(s.tk == TERM)
    {
        fprintf(fp, "%-30s ", node->lex);
    }
    else 
    {
        fprintf(fp, "%-30s ", "---");
    }

    fprintf(fp, "%-30d ", node->lineNo);

    if(s.type == TERM)
    {
        fprintf(fp, "%-30s ", tokenToString(s.tk));
    } 
    else 
    {
        fprintf(fp, "%-30s ", "---");
    }

    if(s.type == TERM && (s.tk == TK_NUM || s.tk == TK_RNUM))
    {
        fprintf(fp, "%-30s", node->lex);
    }
    else 
    {
        fprintf(fp, "%-30s ", "---");
    }

    if(parent != NULL)
    {
        fprintf(fp, "%-30s ", NTtoString(parent->val.nt));
    }
    else 
    {
        fprintf(fp, "%-30s ", "---");
    }

    if(node->noOfChildren == 0)
    {
        fprintf(fp, "%-30s", "Yes");
    }
    else 
    {
        fprintf(fp, "%-30s ", "No");
    }

    if(s.type == NONTERM)
    {
        fprintf(fp, "%-30s\n", NTtoString(s.nt));
    }
    else 
    {
        fprintf(fp, "%-30s\n", "---");
    }
}

void printParseTreeHelper(ParseNodePtr node, ParseNodePtr parent, FILE* fp)
{
    if(node->noOfChildren == 0) printParseNode(node, parent, fp);
    else 
    {
        printParseTreeHelper(node->children[0], node, fp);
        printParseNode(node, parent, fp);
        for(int i = 1; i < node->noOfChildren; i++)
        {
            printParseTreeHelper(node->children[i], node, fp);
        }
    }
}

void printParseTree(ParseTreePtr tree, char* outFile)
{
    FILE* fp = fopen(outFile, "w+");
    if(fp == NULL) printf("Error opening file\n");
    int k = fprintf(fp, "%-30s %-30s %-30s %-30s %-30s %-30s %-30s\n", "lexeme", "lineno", "tokenName", "valueIfNumber", "parentNodeSymbol", "isLeafNode", "NodeSymbol");
    // printf("%d\n", k);
    printParseTreeHelper(tree->root, NULL, fp);
    fclose(fp);
}
