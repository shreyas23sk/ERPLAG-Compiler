// Group No 37
// Shreyas Kumar 2021A7PS2432P
// Prateek Kashyap 2021A7PS1449P
// Harshith Vasireddy 2021A7PS0504P
// Yuvraj Doshi 2021A7PS2425P


#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif

#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

#ifndef LEXER
#define LEXER
#include "lexer.h"
#endif

#ifndef PARSER
#define PARSER
#include "parser.h"
#endif

#include <time.h>

int main(int argc, char* argv[])
{
    int in = 1;
    char* testCaseFileName = argv[1];
    char* parseTreeOutputFileName = argv[2];
    printf("arg file name %s\n", testCaseFileName);
    while(in) 
    {
        printf("Enter\n 0 : exit\n 1: remove comments from test case\n 2: run only the lexer and get the tokens on console\n 3: run the lexer and parser to get parse tre on output file\n 4: get the running time of lexer and parser\n");
        scanf("%d", &in);
        if(in == 0) break;
        else if (in == 1)
        {
            printf("Removing comments...\n");
            removeComments(testCaseFileName, "final.txt");
        }
        else if (in == 2)
        {
            removeComments(testCaseFileName, "final.txt");
            initLexer("final.txt");
            tokenInfo a = getNextToken();
            while(a->plt->val != TK_EOF)
            {
                printf("Line no %d :- Lexeme %-20s Token %-15s\n", a->lineNo, a->plt->lexeme, tokenToString(a->plt->val));
                a = getNextToken();
            }
        }
        else if (in == 3)
        {
            initGrammarRules();
            computeFirstAndFollow();
            removeComments(testCaseFileName, "final.txt");
            ParseTreePtr pt = parseInputSourceCode("final.txt");
            printParseTree(pt, parseTreeOutputFileName);
        }
        else if (in == 4)
        {
            clock_t start_time, end_time;

            double total_CPU_time, total_CPU_time_in_seconds;

            start_time = clock();

            initGrammarRules();
            computeFirstAndFollow();
            removeComments(testCaseFileName, "final.txt");
            ParseTreePtr pt = parseInputSourceCode("final.txt");
            printParseTree(pt, parseTreeOutputFileName);
            end_time = clock();

            total_CPU_time = (double) (end_time - start_time);

            total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;

            printf("Total CPU time = %lf\n", total_CPU_time);
            printf("Total CPU time in seconds = %lf\n", total_CPU_time_in_seconds);
        }
    }
}