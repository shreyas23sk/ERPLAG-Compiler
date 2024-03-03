#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

void initLexer(char *);
tokenInfo getNextToken();
void removeComments(char *,char *);