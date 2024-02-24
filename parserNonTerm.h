#ifndef LEXERTOKENS
#define LEXERTOKENS
#include "lexerTokens.h"
#endif

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

typedef union
{
    TNT type;
    token tk;
    NT nt;
} SYM;

const char *NTtoString(NT);
NT stringToNT(char *);