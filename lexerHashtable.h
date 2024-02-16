// TB Ch2 Sec2.7
#ifndef LEXERTOKENS
#define LEXERTOKENS
#include "lexerTokens.h"
#endif 

struct pairLexemeToken {
    char* lexeme;
    token val;
};
typedef struct pairLexemeToken* pairLexemeToken;

struct hashTable {
    pairLexemeToken* items;
    int size;
};

typedef struct hashTable* hashTable;

pairLexemeToken createPairLexemeToken(char*, TOKEN);
hashTable createEmptyHashTable();

int lookup(hashTable, char*); // return -1 if string s not found, else return index of entry
int insert(hashTable, pairLexemeToken); // returns 1 if new pair successfully inserted, 0 if entry already present