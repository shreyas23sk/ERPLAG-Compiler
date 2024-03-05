// Group No 37
// Shreyas Kumar 2021A7PS2432P
// Prateek Kashyap 2021A7PS1449P
// Harshith Vasireddy 2021A7PS0504P
// Yuvraj Doshi 2021A7PS2425P

#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

pairLexemeToken createPairLexemeToken(const char *s, token tk)
{
    pairLexemeToken newPair = (pairLexemeToken)malloc(sizeof(struct pairLexemeToken));

    if (!newPair)
        return NULL;

    newPair->lexeme = strdup(s);
    if (newPair->lexeme == NULL)
    {
        free(newPair);
        return NULL;
    }

    newPair->val = tk;
    return newPair;
}
