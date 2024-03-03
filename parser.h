#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif

void initGrammarRules();
tokenSet computeFirstList(NodePtr rhs);
void computeFirstAndFollow();