enum TOKEN
{
    TK_COMMENT,
    TK_ASSIGNOP,
    TK_NUM,
    TK_RNUM,
    TK_ID,
    TK_FIELDID,
    TK_FUNID,
    TK_RUID,
    TK_GT,
    TK_GE,
    TK_LT,
    TK_LE,
    TK_NE,
    TK_EQ,
    TK_PARAMETERS,
    TK_WITH,
    TK_END,
    TK_WHILE,
    TK_END,
    TK_UNION,
    TK_ENDUNION,
    TK_DEFINETYPE,
    TK_AS,
    TK_TYPE,
    TK_MAIN,
    TK_GLOBAL,
    TK_LIST,
    TK_INPUT,
    TK_OUTPUT,
    TK_INT,
    TK_REAL,
    TK_ENDWHILE,
    TK_IF,
    TK_THEN,
    TK_ENDIF,
    TK_READ,
    TK_WRITE,
    TK_RETURN,
    TK_CALL,
    TK_RECORD,
    TK_ENDRECORD,
    TK_ELSE,
    TK_SQL,
    TK_SQR,
    TK_COMMA,
    TK_SEM,
    TK_COLON,
    TK_DOT,
    TK_OP,
    TK_CL,
    TK_PLUS,
    TK_MINUS,
    TK_MUL,
    TK_DIV,
    TK_NOT,
    TK_AND,
    TK_OR,
    TK_PARAMETER
};

typedef enum TOKEN token;
char *tokenToString(token);
token stringToToken(char *);