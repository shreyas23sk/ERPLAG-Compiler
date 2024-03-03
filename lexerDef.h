#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 2048

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

struct twinBuffer
{
    FILE *fp;
    char buffer[2][BUFLEN];
    char *forward, *begin;
    int forwardBufferNo, beginBufferNo;
    int retractions;
    int lineNo;
};
typedef struct twinBuffer *twinBuffer;

struct pairLexemeToken
{
    char *lexeme;
    token val;
};
typedef struct pairLexemeToken *pairLexemeToken;

struct tokenInfo
{
    pairLexemeToken plt;
    int lineNo;
    int isNumber; // 0 for no, 1 for TK_NUM, 2 for TK_REAL
    char *valueIfNumber;
};
typedef struct tokenInfo *tokenInfo;

struct hashTable
{
    pairLexemeToken *items;
    int size;
};
typedef struct hashTable *hashTable;

token stringToToken(char *);
const char *tokenToString(token);

pairLexemeToken createPairLexemeToken(const char *, token);

tokenInfo createTokenInfo(pairLexemeToken plt, twinBuffer B);

hashTable createEmptyHashTable();
int lookup(hashTable, const char *);
int insert(hashTable, const char *, token);
int insertInTable(hashTable, pairLexemeToken);

twinBuffer initBuffer(char *);
char nextChar(twinBuffer);
twinBuffer reload(twinBuffer);
twinBuffer advance(twinBuffer);
twinBuffer retract(twinBuffer);
twinBuffer resetBegin(twinBuffer);
char *getLexeme(twinBuffer);