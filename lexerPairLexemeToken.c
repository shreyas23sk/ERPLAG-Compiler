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
