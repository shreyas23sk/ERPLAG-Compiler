#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

tokenInfo createTokenInfo(pairLexemeToken plt, twinBuffer B)
{
    tokenInfo ti = (tokenInfo)malloc(sizeof(struct tokenInfo));

    if (!ti)
        return NULL;

    ti->plt = plt;

    if (plt->val == TK_NUM || plt->val == TK_REAL)
    {
        ti->isNumber = (plt->val == TK_NUM) ? 1 : 2;
        ti->valueIfNumber = plt->lexeme;
    }
    else
    {
        ti->isNumber = 0;
        ti->valueIfNumber = NULL;
    }
    
    ti->lineNo = B->lineNo;
    return ti;
}