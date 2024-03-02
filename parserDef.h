#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

#include "string.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    program,
    otherFunctions,
    mainFunction,
    EPSILON,
    input_par,
    output_par,
    dataType,
    primitiveDatatype,
    constructedDatatype,
    remaining_list,
    stmts,
    typeDefinitions,
    typeDefinition,
    fieldDefinitions,
    fieldDefinition,
    moreFields,
    declarations,
    declaration,
    global_or_not,
    otherStmts,
    stmt,
    assignmentStmt,
    iterativeStmt,
    conditionalStmt,
    ioStmt,
    funCallStmt,
    option_single_constructed,
    oneExpansion,
    moreExpansion,
    term,
    expPrime,
    factor,
    termPrime,
    var,
    afterNotBooleanExpression,
    booleanExpression,
    not,
    singleOrRecId,
    logicalOp,
    relationalOp,
    returnStmt,
    optionalReturn,
    idList,
    more_ids,
    definetypestmt,
    A,
    outputParameters
} NT;

typedef enum
{
    TERM,
    NONTERM
} TNT;

typedef struct
{
    TNT type;
    token tk;
    NT nt;
} SYM;

const char *NTtoString(NT);
NT stringToNT(char *);

// Linked List
typedef struct Node {
    SYM data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} LinkedList;

typedef Node* NodePtr;
typedef LinkedList* LinkedListPtr;

// Stack
typedef struct {
    LinkedListPtr ll;
} Stack;
typedef Stack* StackPtr;

// Parse Tree
typedef struct ParseNode {
    SYM val;
    struct ParseNode** children;
    int noOfChildren;
} ParseNode;

typedef struct ParseTree {
    struct ParseNode* root;
} ParseTree;

typedef ParseNode* ParseNodePtr;
typedef ParseTree* ParseTreePtr;

LinkedListPtr createLinkedList();
NodePtr createNode(SYM newData);
void insertNode(LinkedListPtr list, SYM newData);
void deleteNode(LinkedListPtr list, SYM dataToDelete);

StackPtr createStack();
void push(StackPtr stack, SYM newData);
SYM pop(StackPtr stack);
SYM peek(StackPtr stack);
int isStackEmpty(StackPtr stack);

ParseTreePtr createParseTree();
ParseNodePtr createParseNode(SYM value);
void addChild(ParseNodePtr parent, SYM value);
void printParseTree(ParseTreePtr tree);
