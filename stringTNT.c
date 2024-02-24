#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif

NT stringToNT(char *str)
{
    if (strcmp(str, "program") == 0)
    {
        return program;
    }
    else if (strcmp(str, "otherFunctions") == 0)
    {
        return otherFunctions;
    }
    else if (strcmp(str, "mainFunction") == 0)
    {
        return mainFunction;
    }
    else if (strcmp(str, "EPSILON") == 0)
    {
        return EPSILON;
    }
    else if (strcmp(str, "input_par") == 0)
    {
        return input_par;
    }
    else if (strcmp(str, "output_par") == 0)
    {
        return output_par;
    }
    else if (strcmp(str, "dataType") == 0)
    {
        return dataType;
    }
    else if (strcmp(str, "primitiveDatatype") == 0)
    {
        return primitiveDatatype;
    }
    else if (strcmp(str, "constructedDatatype") == 0)
    {
        return constructedDatatype;
    }
    else if (strcmp(str, "remaining_list") == 0)
    {
        return remaining_list;
    }
    else if (strcmp(str, "stmts") == 0)
    {
        return stmts;
    }
    else if (strcmp(str, "typeDefinitions") == 0)
    {
        return typeDefinitions;
    }
    else if (strcmp(str, "typeDefinition") == 0)
    {
        return typeDefinition;
    }
    else if (strcmp(str, "fieldDefinitions") == 0)
    {
        return fieldDefinitions;
    }
    else if (strcmp(str, "fieldDefinition") == 0)
    {
        return fieldDefinition;
    }
    else if (strcmp(str, "moreFields") == 0)
    {
        return moreFields;
    }
    else if (strcmp(str, "declarations") == 0)
    {
        return declarations;
    }
    else if (strcmp(str, "declaration") == 0)
    {
        return declaration;
    }
    else if (strcmp(str, "global_or_not") == 0)
    {
        return global_or_not;
    }
    else if (strcmp(str, "otherStmts") == 0)
    {
        return otherStmts;
    }
    else if (strcmp(str, "stmt") == 0)
    {
        return stmt;
    }
    else if (strcmp(str, "assignmentStmt") == 0)
    {
        return assignmentStmt;
    }
    else if (strcmp(str, "iterativeStmt") == 0)
    {
        return iterativeStmt;
    }
    else if (strcmp(str, "conditionalStmt") == 0)
    {
        return conditionalStmt;
    }
    else if (strcmp(str, "ioStmt") == 0)
    {
        return ioStmt;
    }
    else if (strcmp(str, "funCallStmt") == 0)
    {
        return funCallStmt;
    }
    else if (strcmp(str, "option_single_constructed") == 0)
    {
        return option_single_constructed;
    }
    else if (strcmp(str, "oneExpansion") == 0)
    {
        return oneExpansion;
    }
    else if (strcmp(str, "moreExpansion") == 0)
    {
        return moreExpansion;
    }
    else if (strcmp(str, "term") == 0)
    {
        return term;
    }
    else if (strcmp(str, "expPrime") == 0)
    {
        return expPrime;
    }
    else if (strcmp(str, "factor") == 0)
    {
        return factor;
    }
    else if (strcmp(str, "termPrime") == 0)
    {
        return termPrime;
    }
    else if (strcmp(str, "var") == 0)
    {
        return var;
    }
    else if (strcmp(str, "afterNotBooleanExpression") == 0)
    {
        return afterNotBooleanExpression;
    }
    else if (strcmp(str, "booleanExpression") == 0)
    {
        return booleanExpression;
    }
    else if (strcmp(str, "not") == 0)
    {
        return not ;
    }
    else if (strcmp(str, "singleOrRecId") == 0)
    {
        return singleOrRecId;
    }
    else if (strcmp(str, "logicalOp") == 0)
    {
        return logicalOp;
    }
    else if (strcmp(str, "relationalOp") == 0)
    {
        return relationalOp;
    }
    else if (strcmp(str, "returnStmt") == 0)
    {
        return returnStmt;
    }
    else if (strcmp(str, "optionalReturn") == 0)
    {
        return optionalReturn;
    }
    else if (strcmp(str, "idList") == 0)
    {
        return idList;
    }
    else if (strcmp(str, "more_ids") == 0)
    {
        return more_ids;
    }
    else if (strcmp(str, "definetypestmt") == 0)
    {
        return definetypestmt;
    }
    else if (strcmp(str, "A") == 0)
    {
        return A;
    }
    else if (strcmp(str, "outputParameters") == 0)
    {
        return outputParameters;
    }
    else
    {
        /* Handle invalid input */
        return -1;
    }
}

const char *NTtoString(NT nt)
{
    switch (nt)
    {
    case program:
        return "program";
    case otherFunctions:
        return "otherFunctions";
    case mainFunction:
        return "mainFunction";
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
    case assignmentStmt:
        return "assignmentStmt";
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
        /* Handle unknown NT value */
        exit(-1);
    }
}

const char *tokenToString(token t)
{
    switch (t)
    {
    case TK_COMMENT:
        return "TK_COMMENT";
    case TK_ASSIGNOP:
        return "TK_ASSIGNOP";
    case TK_NUM:
        return "TK_NUM";
    case TK_RNUM:
        return "TK_RNUM";
    case TK_ID:
        return "TK_ID";
    case TK_FIELDID:
        return "TK_FIELDID";
    case TK_FUNID:
        return "TK_FUNID";
    case TK_RUID:
        return "TK_RUID";
    case TK_GT:
        return "TK_GT";
    case TK_GE:
        return "TK_GE";
    case TK_LT:
        return "TK_LT";
    case TK_LE:
        return "TK_LE";
    case TK_NE:
        return "TK_NE";
    case TK_EQ:
        return "TK_EQ";
    case TK_PARAMETERS:
        return "TK_PARAMETERS";
    case TK_WITH:
        return "TK_WITH";
    case TK_END:
        return "TK_END";
    case TK_WHILE:
        return "TK_WHILE";
    case TK_UNION:
        return "TK_UNION";
    case TK_ENDUNION:
        return "TK_ENDUNION";
    case TK_DEFINETYPE:
        return "TK_DEFINETYPE";
    case TK_AS:
        return "TK_AS";
    case TK_TYPE:
        return "TK_TYPE";
    case TK_MAIN:
        return "TK_MAIN";
    case TK_GLOBAL:
        return "TK_GLOBAL";
    case TK_LIST:
        return "TK_LIST";
    case TK_INPUT:
        return "TK_INPUT";
    case TK_OUTPUT:
        return "TK_OUTPUT";
    case TK_INT:
        return "TK_INT";
    case TK_REAL:
        return "TK_REAL";
    case TK_ENDWHILE:
        return "TK_ENDWHILE";
    case TK_IF:
        return "TK_IF";
    case TK_THEN:
        return "TK_THEN";
    case TK_ENDIF:
        return "TK_ENDIF";
    case TK_READ:
        return "TK_READ";
    case TK_WRITE:
        return "TK_WRITE";
    case TK_RETURN:
        return "TK_RETURN";
    case TK_CALL:
        return "TK_CALL";
    case TK_RECORD:
        return "TK_RECORD";
    case TK_ENDRECORD:
        return "TK_ENDRECORD";
    case TK_ELSE:
        return "TK_ELSE";
    case TK_SQL:
        return "TK_SQL";
    default:
        return "<unknown>";
    }
}
token stringToToken(char *str)
{
    if (!strcmp(str, "TK_COMMENT"))
        return TK_COMMENT;
    else if (!strcmp(str, "TK_ASSIGNOP"))
        return TK_ASSIGNOP;
    else if (!strcmp(str, "TK_NUM"))
        return TK_NUM;
    else if (!strcmp(str, "TK_RNUM"))
        return TK_RNUM;
    else if (!strcmp(str, "TK_ID"))
        return TK_ID;
    else if (!strcmp(str, "TK_FIELDID"))
        return TK_FIELDID;
    else if (!strcmp(str, "TK_FUNID"))
        return TK_FUNID;
    else if (!strcmp(str, "TK_RUID"))
        return TK_RUID;
    else if (!strcmp(str, "TK_GT"))
        return TK_GT;
    else if (!strcmp(str, "TK_GE"))
        return TK_GE;
    else if (!strcmp(str, "TK_LT"))
        return TK_LT;
    else if (!strcmp(str, "TK_LE"))
        return TK_LE;
    else if (!strcmp(str, "TK_NE"))
        return TK_NE;
    else if (!strcmp(str, "TK_EQ"))
        return TK_EQ;
    else if (!strcmp(str, "TK_PARAMETERS"))
        return TK_PARAMETERS;
    else if (!strcmp(str, "TK_WITH"))
        return TK_WITH;
    else if (!strcmp(str, "TK_END"))
        return TK_END;
    else if (!strcmp(str, "TK_WHILE"))
        return TK_WHILE;
    else if (!strcmp(str, "TK_ENDWHILE"))
        return TK_ENDWHILE;
    else if (!strcmp(str, "TK_IF"))
        return TK_IF;
    else if (!strcmp(str, "TK_THEN"))
        return TK_THEN;
    else if (!strcmp(str, "TK_ENDIF"))
        return TK_ENDIF;
    else if (!strcmp(str, "TK_READ"))
        return TK_READ;
    else if (!strcmp(str, "TK_WRITE"))
        return TK_WRITE;
    else if (!strcmp(str, "TK_RETURN"))
        return TK_RETURN;
    else if (!strcmp(str, "TK_CALL"))
        return TK_CALL;
    else if (!strcmp(str, "TK_RECORD"))
        return TK_RECORD;
    else if (!strcmp(str, "TK_ENDRECORD"))
        return TK_ENDRECORD;
    else if (!strcmp(str, "TK_ELSE"))
        return TK_ELSE;
    else if (!strcmp(str, "TK_SQL"))
        return TK_SQL;
    else if (!strcmp(str, "TK_SQR"))
        return TK_SQR;
    else if (!strcmp(str, "TK_COMMA"))
        return TK_COMMA;
    else if (!strcmp(str, "TK_SEM"))
        return TK_SEM;
    else if (!strcmp(str, "TK_COLON"))
        return TK_COLON;
    else if (!strcmp(str, "TK_DOT"))
        return TK_DOT;
    else if (!strcmp(str, "TK_OP"))
        return TK_OP;
    else if (!strcmp(str, "TK_CL"))
        return TK_CL;
    else if (!strcmp(str, "TK_PLUS"))
        return TK_PLUS;
    else if (!strcmp(str, "TK_MINUS"))
        return TK_MINUS;
    else if (!strcmp(str, "TK_MUL"))
        return TK_MUL;
    else if (!strcmp(str, "TK_DIV"))
        return TK_DIV;
    else if (!strcmp(str, "TK_NOT"))
        return TK_NOT;
    else if (!strcmp(str, "TK_AND"))
        return TK_AND;
    else if (!strcmp(str, "TK_OR"))
        return TK_OR;
    else if (!strcmp(str, "TK_PARAMETER"))
        return TK_PARAMETER;
    exit(-1);
}