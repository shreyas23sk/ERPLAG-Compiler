#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif

void initGrammarRules();
token computeFirstList(NodePtr rhs);
void computeFirstAndFollow();