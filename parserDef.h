// Group No 37
// Shreyas Kumar 2021A7PS2432P
// Prateek Kashyap 2021A7PS1449P
// Harshith Vasireddy 2021A7PS0504P
// Yuvraj Doshi 2021A7PS2425P

#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

typedef enum
{
    program,
    otherFunctions,
    mainFunction,
    function,
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
    fieldType,
    moreFields,
    declarations,
    declaration,
    global_or_not,
    otherStmts,
    stmt,
    assignmentStmt,
    arithmeticExpression,
    iterativeStmt,
    conditionalStmt,
    ioStmt,
    funCallStmt,
    option_single_constructed,
    oneExpansion,
    moreExpansion,
    inputParameters,
    endOrElse,
    term,
    expPrime,
    factor,
    termPrime,
    var,
    booleanExpression,
    singleOrRecId,
    logicalOp,
    relationalOp,
    returnStmt,
    optionalReturn,
    idList,
    more_ids,
    definetypestmt,
    A,
    outputParameters,
    parameter_list,
    actualOrRedefined,
    highPrecedenceOperator,
    lowPrecedenceOperator
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

typedef struct Node
{
    SYM data;
    struct Node *next;
    struct Node *prev;
} Node;
typedef Node *NodePtr;

typedef struct
{
    Node *head;
    Node *tail;
} LinkedList;
typedef LinkedList *LinkedListPtr;

typedef struct ParseNode
{
    SYM val;
    int lineNo;
    char* lex;
    struct ParseNode **children;
    int noOfChildren;
} ParseNode;
typedef ParseNode *ParseNodePtr;

typedef struct ParseTree
{
    struct ParseNode *root;
} ParseTree;
typedef ParseTree *ParseTreePtr;

typedef struct ParseNodeLL
{
    struct ParseNodeLL *next;
    struct ParseNodeLL *prev;
    ParseNodePtr val;
} ParseNodeLL;
typedef ParseNodeLL *ParseNodeLLPtr;

typedef struct Stack
{
    ParseNodeLLPtr top;
    ParseNodeLLPtr tail;
} Stack;
typedef Stack *StackPtr;

typedef struct
{
    token *set;
    int eps;
    int endOfInput;
    int size;
} TKSET;
typedef TKSET *tokenSet;

NT stringToNT(char *);
const char *NTtoString(NT);

LinkedListPtr createLinkedList();
NodePtr createNode(SYM newData);
void insertNode(LinkedListPtr list, SYM newData);
void printList(LinkedListPtr ptr);

StackPtr createStack();
void push(StackPtr stack, ParseNodePtr node);
ParseNodePtr pop(StackPtr stack);
ParseNodePtr peek(StackPtr stack);
int isEmpty(StackPtr stack);

ParseTreePtr createParseTree();
ParseNodePtr createParseNode(SYM value, int lineNo, char* lex);
void addChild(ParseNodePtr parent, ParseNodePtr child);
void printParseTreeHelper(ParseNodePtr node, ParseNodePtr parent, FILE *fp);
void printParseTree(ParseTreePtr tree, char* outFile);
