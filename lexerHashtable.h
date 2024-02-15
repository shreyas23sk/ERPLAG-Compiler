// TB Ch2 Sec2.7
#ifndef LEXERTOKENS
#define LEXERTOKENS
#include "lexerTokens.h"
#endif 

struct pairLexemeToken {
    char* lexeme;
    TOKEN val;
};
typedef struct pairLexemeToken* pairLexemeToken

typedef struct hashTable {
    pairLexemeToken* items;
    int size;
} hashTable;

pairLexemeToken createPairLexemeToken(char*, TOKEN);
int lookup(hashTable, char*); // return -1 if string s not found, else return index of entry
int insert(hashTable, pairLexemeToken);