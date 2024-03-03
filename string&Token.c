#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif

token stringToToken(char *str)
{
    if (!strcmp(str, "TK_COMMENT"))
        return TK_COMMENT;

    else if (!strcmp(str, "TK_ASSIGNOP"))
        return TK_ASSIGNOP;

    else if (!strcmp(str, "TK_UNION"))
        return TK_UNION;

    else if (!strcmp(str, "TK_ENDUNION"))
        return TK_ENDUNION;

    else if (!strcmp(str, "TK_TYPE"))
        return TK_TYPE;

    else if (!strcmp(str, "TK_GLOBAL"))
        return TK_GLOBAL;

    else if (!strcmp(str, "TK_DEFINETYPE"))
        return TK_DEFINETYPE;

    else if (!strcmp(str, "TK_AS"))
        return TK_AS;

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

    else if (!strcmp(str, "TK_INPUT"))
        return TK_INPUT;

    else if (!strcmp(str, "TK_LIST"))
        return TK_LIST;

    else if (!strcmp(str, "TK_OUTPUT"))
        return TK_OUTPUT;

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

    else if (!strcmp(str, "TK_INT"))
        return TK_INT;

    else if (!strcmp(str, "TK_REAL"))
        return TK_REAL;

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

    else if (!strcmp(str, "TK_MAIN"))
        return TK_MAIN;

    else
        exit(-1);
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

    case TK_MUL:
        return "TK_MUL";

    case TK_DIV:
        return "TK_DIV";

    case TK_PLUS:
        return "TK_PLUS";

    case TK_MINUS:
        return "TK_MINUS";

    case TK_COMMA:
        return "TK_COMMA";

    case TK_DOT:
        return "TK_DOT";

    case TK_NOT:
        return "TK_NOT";

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

    case TK_AND:
        return "TK_AND";

    case TK_COLON:
        return "TK_COLON";

    case TK_OR:
        return "TK_OR";

    case TK_CL:
        return "TK_CL";

    case TK_OP:
        return "TK_OP";

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

    case TK_SEM:
        return "TK_SEM";

    case TK_PARAMETER:
        return "TK_PARAMETER";

    case TK_SQR:
        return "TK_SQR";

    default:
        return "<unknown>";
    }
}
