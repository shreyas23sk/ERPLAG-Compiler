#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif

void initGrammarRules();
void computeFirstAndFollow();
ParseTreePtr parseInputSourceCode(char *testCaseFileName);