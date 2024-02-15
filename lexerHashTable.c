#ifndef LEXERHASHTABLE
#define LEXERHASHTABLE
#include "lexerHashTable.h"
#endif

pairLexemeToken createPairLexemeToken(char* s, TOKEN tk) {
    pairLexemeToken newPair = (pairLexemeToken) malloc(sizeof(pairLexemeToken));
    newPair->lexeme = s;
    newPair->val = tk;
    return newPair;
}