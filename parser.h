// Group No 37
// Shreyas Kumar 2021A7PS2432P
// Prateek Kashyap 2021A7PS1449P
// Harshith Vasireddy 2021A7PS0504P
// Yuvraj Doshi 2021A7PS2425P

#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif

void initGrammarRules();
void computeFirstAndFollow();
ParseTreePtr parseInputSourceCode(char *testCaseFileName);