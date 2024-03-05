// Group No 37
// Shreyas Kumar 2021A7PS2432P
// Prateek Kashyap 2021A7PS1449P
// Harshith Vasireddy 2021A7PS0504P
// Yuvraj Doshi 2021A7PS2425P

#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

void initLexer(char *);
tokenInfo getNextToken();
int isAtEndOfInput();
void removeComments(char *, char *);