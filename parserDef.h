#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

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
