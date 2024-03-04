#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

void initLexer(char *);
tokenInfo getNextToken();
int isAtEndOfInput();
void removeComments(char *, char *);