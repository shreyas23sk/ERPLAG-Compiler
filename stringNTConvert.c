#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif

NT stringToNT(char *str)
{
    if (!strcmp(str, "program"))
        return program;

    else if (!strcmp(str, "fieldType"))
        return fieldType;

    else if (!strcmp(str, "inputParameters"))
        return inputParameters;

    else if (!strcmp(str, "endOrElse"))
        return endOrElse;

    else if (!strcmp(str, "assignmentStmt"))
        return assignmentStmt;

    else if (!strcmp(str, "highPrecdenceOperator"))
        return highPrecedenceOperator;

    else if (!strcmp(str, "lowPrecedenceOperator"))
        return lowPrecedenceOperator;

    else if (!strcmp(str, "otherFunctions"))
        return otherFunctions;

    else if (!strcmp(str, "mainFunction"))
        return mainFunction;

    else if (!strcmp(str, "actualOrRedefined"))
        return actualOrRedefined;

    else if (!strcmp(str, "arithmeticExpression"))
        return arithmeticExpression;

    else if (!strcmp(str, "parameter_list"))
        return parameter_list;

    else if (!strcmp(str, "function"))
        return function;

    else if (!strcmp(str, "EPSILON"))
        return EPSILON;

    else if (!strcmp(str, "input_par"))
        return input_par;

    else if (!strcmp(str, "output_par"))
        return output_par;

    else if (!strcmp(str, "dataType"))
        return dataType;

    else if (!strcmp(str, "primitiveDatatype"))
        return primitiveDatatype;

    else if (!strcmp(str, "constructedDatatype"))
        return constructedDatatype;

    else if (!strcmp(str, "remaining_list"))
        return remaining_list;

    else if (!strcmp(str, "stmts"))
        return stmts;

    else if (!strcmp(str, "typeDefinitions"))
        return typeDefinitions;

    else if (!strcmp(str, "typeDefinition"))
        return typeDefinition;

    else if (!strcmp(str, "fieldDefinitions"))
        return fieldDefinitions;

    else if (!strcmp(str, "fieldDefinition"))
        return fieldDefinition;

    else if (!strcmp(str, "moreFields"))
        return moreFields;

    else if (!strcmp(str, "declarations"))
        return declarations;

    else if (!strcmp(str, "declaration"))
        return declaration;

    else if (!strcmp(str, "global_or_not"))
        return global_or_not;

    else if (!strcmp(str, "otherStmts"))
        return otherStmts;

    else if (!strcmp(str, "stmt"))
        return stmt;

    else if (!strcmp(str, "assignmentStmt"))
        return assignmentStmt;

    else if (!strcmp(str, "iterativeStmt"))
        return iterativeStmt;

    else if (!strcmp(str, "conditionalStmt"))
        return conditionalStmt;

    else if (!strcmp(str, "ioStmt"))
        return ioStmt;

    else if (!strcmp(str, "funCallStmt"))
        return funCallStmt;

    else if (!strcmp(str, "option_single_constructed"))
        return option_single_constructed;

    else if (!strcmp(str, "oneExpansion"))
        return oneExpansion;

    else if (!strcmp(str, "moreExpansion"))
        return moreExpansion;

    else if (!strcmp(str, "term"))
        return term;

    else if (!strcmp(str, "expPrime"))
        return expPrime;

    else if (!strcmp(str, "factor"))
        return factor;

    else if (!strcmp(str, "termPrime"))
        return termPrime;

    else if (!strcmp(str, "var"))
        return var;

    else if (!strcmp(str, "afterNotBooleanExpression"))
        return afterNotBooleanExpression;

    else if (!strcmp(str, "booleanExpression"))
        return booleanExpression;

    else if (!strcmp(str, "not"))
        return not ;

    else if (!strcmp(str, "singleOrRecId"))
        return singleOrRecId;

    else if (!strcmp(str, "logicalOp"))
        return logicalOp;

    else if (!strcmp(str, "relationalOp"))
        return relationalOp;

    else if (!strcmp(str, "returnStmt"))
        return returnStmt;

    else if (!strcmp(str, "optionalReturn"))
        return optionalReturn;

    else if (!strcmp(str, "idList"))
        return idList;

    else if (!strcmp(str, "more_ids"))
        return more_ids;

    else if (!strcmp(str, "definetypestmt"))
        return definetypestmt;

    else if (!strcmp(str, "A"))
        return A;

    else if (!strcmp(str, "outputParameters"))
        return outputParameters;

    else
        return -1; // Invalid Inputs
}

const char *NTtoString(NT nt)
{
    switch (nt)
    {
    case program:
        return "program";

    case otherFunctions:
        return "otherFunctions";

    case fieldType:
        return "fieldType";

    case arithmeticExpression:
        return "arithmeticExpression";

    case parameter_list:
        return "parameter_list";

    case mainFunction:
        return "mainFunction";

    case actualOrRedefined:
        return "actualOrRedefined";

    case function:
        return "function";

    case highPrecedenceOperator:
        return "highPrecdenceOperator";

    case lowPrecedenceOperator:
        return "lowPrecedenceOperator";

    case assignmentStmt:
        return "assignmentStmt";

    case inputParameters:
        return "inputParameters";

    case endOrElse:
        return "endOrElse";

    case EPSILON:
        return "EPSILON";

    case input_par:
        return "input_par";

    case output_par:
        return "output_par";

    case dataType:
        return "dataType";

    case primitiveDatatype:
        return "primitiveDatatype";

    case constructedDatatype:
        return "constructedDatatype";

    case remaining_list:
        return "remaining_list";

    case stmts:
        return "stmts";

    case typeDefinitions:
        return "typeDefinitions";

    case typeDefinition:
        return "typeDefinition";

    case fieldDefinitions:
        return "fieldDefinitions";

    case fieldDefinition:
        return "fieldDefinition";

    case moreFields:
        return "moreFields";

    case declarations:
        return "declarations";

    case declaration:
        return "declaration";

    case global_or_not:
        return "global_or_not";

    case otherStmts:
        return "otherStmts";

    case stmt:
        return "stmt";

    case iterativeStmt:
        return "iterativeStmt";

    case conditionalStmt:
        return "conditionalStmt";

    case ioStmt:
        return "ioStmt";

    case funCallStmt:
        return "funCallStmt";

    case option_single_constructed:
        return "option_single_constructed";

    case oneExpansion:
        return "oneExpansion";

    case moreExpansion:
        return "moreExpansion";

    case term:
        return "term";

    case expPrime:
        return "expPrime";

    case factor:
        return "factor";

    case termPrime:
        return "termPrime";

    case var:
        return "var";

    case afterNotBooleanExpression:
        return "afterNotBooleanExpression";

    case booleanExpression:
        return "booleanExpression";

    case not:
        return "not";

    case singleOrRecId:
        return "singleOrRecId";

    case logicalOp:
        return "logicalOp";

    case relationalOp:
        return "relationalOp";

    case returnStmt:
        return "returnStmt";

    case optionalReturn:
        return "optionalReturn";

    case idList:
        return "idList";

    case more_ids:
        return "more_ids";

    case definetypestmt:
        return "definetypestmt";

    case A:
        return "A";

    case outputParameters:
        return "outputParameters";

    default:
        exit(-1); /* Unknown NT Value */
    }
}
