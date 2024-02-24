#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif

#define noOfRules 94
#define maxSizeOfTNT 26

LinkedListPtr* grammar;

SYM createSYM(TNT type, char* str) 
{
    SYM data;
    data.type = type;
    if(type == TERM) {
        data.tk = stringToToken(str);
    } else {
        data.nt = stringToNT(str);
    }
}

void initGrammarRules() {
    grammar = (LinkedListPtr *) malloc(sizeof(LinkedListPtr) * noOfRules);
    int gIndex = 0;

    FILE* fp = fopen("grammar.txt", "ab");

    char tnt[maxSizeOfTNT];
    memset(tnt, '\0', sizeof(tnt));

    grammar[0] = createLinkedList();
    while(1)
    {
        char c = fgetc(fp);
        if(c == ' ') 
        {
            if(tnt[0] != '\0') // current string is not empty
            {
                SYM data;
                if(tnt[0] == 'T') 
                {
                    data = createSYM(TERM, tnt);
                } 
                else 
                {
                    data = createSYM(NONTERM, tnt);
                }
                printf("%s ", tnt);
                insertNode(grammar[gIndex], data);
                memset(tnt, '\0', sizeof(tnt));
            }
        }
        else if (c == '\n') 
        {
            if(tnt[0] != '\0') // current string is not empty
            {
                SYM data;
                if(tnt[0] == 'T') 
                {
                    data = createSYM(TERM, tnt);
                } 
                else 
                {
                    data = createSYM(NONTERM, tnt);
                }
                printf("\n%s ", tnt);
                insertNode(grammar[gIndex], data);
                memset(tnt, '\0', sizeof(tnt));
            }

            gIndex++;
            grammar[gIndex] = createLinkedList();
        }
        else if (c == '|') 
        {
            if(tnt[0] != '\0') // current string is not empty
            {
                SYM data;
                if(tnt[0] == 'T') 
                {
                    data = createSYM(TERM, tnt);
                } 
                else 
                {
                    data = createSYM(NONTERM, tnt);
                }
                printf("\n%s ", tnt);
                insertNode(grammar[gIndex], data);
                memset(tnt, '\0', sizeof(tnt));
            }
            
            gIndex++;
            grammar[gIndex] = createLinkedList();
            insertNode(grammar[gIndex], grammar[gIndex - 1]->head->data);
        }

        if(feof(fp)) break;
    }
}