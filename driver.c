#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "parser.h"

#include "lexerDef.h"
#include "parserDef.h"

int main()
{
    initGrammarRules();
    computeFirstAndFollow();
    removeComments("testcase.txt", "final.txt");
    ParseTreePtr pt = parseInputSourceCode("final.txt");
}