// Group No 37
// Shreyas Kumar 2021A7PS2432P
// Prateek Kashyap 2021A7PS1449P
// Harshith Vasireddy 2021A7PS0504P
// Yuvraj Doshi 2021A7PS2425P

#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

hashTable createHashTable()
{
    hashTable newTable = (hashTable)malloc(sizeof(struct hashTable));

    newTable->size = 0;
    newTable->items = NULL;

    return newTable;
}

int lookup(hashTable ht, char *s)
{
    if (ht->size == 0)
        return -1;

    for (int i = 0; i < ht->size; i++)
    {
        if (strcmp(ht->items[i]->lexeme, s) == 0)
            return i;
    }

    return -1;
}

int insert(hashTable ht, const char *s, token tk)
{
    pairLexemeToken plt = createPairLexemeToken(s, tk);

    if (!plt)
        return 0;

    int inserted = insertInTable(ht, plt);

    if (!inserted)
    {
        free(plt->lexeme);
        free(plt);
    }

    return inserted;
}

int insertInTable(hashTable ht, pairLexemeToken plt)
{
    if (lookup(ht, plt->lexeme) < 0)
    {
        ht->size++;
        ht->items = (pairLexemeToken *)realloc(ht->items, sizeof(pairLexemeToken) * (ht->size));

        if (ht->items == NULL)
        {
            ht->size--;
            return 0;
        }

        ht->items[ht->size - 1] = plt;
        return 1;
    }
    else
    {
        return 0;
    }
}