#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

pairLexemeToken createPairLexemeToken(char *s, token tk)
{
    pairLexemeToken newPair = (pairLexemeToken)malloc(sizeof(struct pairLexemeToken));
    newPair->lexeme = s;
    newPair->val = tk;
    return newPair;
}

hashTable createEmptyHashTable()
{
    hashTable newTable = (hashTable)malloc(sizeof(struct hashTable));
    newTable->size = 0;
    return newTable;
}

int lookup(hashTable ht, char *s)
{
    for (int i = 0; i < ht->size; i++)
    {
        if (strcmp(ht->items[i]->lexeme, s) == 0)
            return i;
    }
    return -1;
}

int insert(hashTable ht, pairLexemeToken plt)
{
    if (lookup(ht, plt->lexeme) < 0)
    {
        ht->size++;
        ht->items = (pairLexemeToken *)realloc(ht->items, sizeof(pairLexemeToken) * (ht->size));
        ht->items[ht->size - 1] = plt;
        return 1;
    }
    else
        return 0;
}