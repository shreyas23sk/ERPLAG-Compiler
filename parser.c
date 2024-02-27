#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif

#define NO_OF_RULES 94
#define MAX_SIZE_OF_TNT 26
#define NO_OF_TERMS 58 
#define NO_OF_NONTERMS 47

typedef struct {
    token* set;
    int size;
} TKSET;
typedef TKSET* tokenSet;

LinkedListPtr* grammar;
int nullable[NO_OF_NONTERMS];
tokenSet firstSet[NO_OF_NONTERMS];
tokenSet followSet[NO_OF_NONTERMS] = {NULL};

tokenSet addTokenToTokenSet(tokenSet S, token tk) {
    if(S->size == 0) {
        S->set = (token *) malloc(sizeof(token));
        S->set[0] = tk; S->size++;
        return S;
    } else {
        S->set = (token *) realloc(S->set, S->size + 1);
        S->set[S->size] = tk;
        S->size++;
    }
} 

// A = A union B if withEpsilon = 1
// A = A union B - {EPSILON} otherwise
tokenSet unionTokenSet(tokenSet A, tokenSet B, int withEpsilon) {
    int inSetA[NO_OF_TERMS] = {0};
    int inSetB[NO_OF_TERMS] = {0};

    for(int i = 0; i < A->size; i++) {
        inSetA[A->set[i]] = 1;
    }

    for(int i = 0; i < B->size; i++) {
        inSetB[B->set[i]] = 1;
    }

    int noOfTokensToBeAddedToA = 0;
    for(int i = 0; i < NO_OF_TERMS; i++) {
        noOfTokensToBeAddedToA += (~inSetA[i] & inSetB[i]);
    }

    int totalSize = A->size + noOfTokensToBeAddedToA;
    A->set = (token *) realloc(A->set, totalSize);
    
    int j = 0;
    for(int i = TK_COMMENT; i <= TK_PARAMETER; i++) {
        if(~inSetA[i] & inSetB[i]) {
            A->set[A->size + (j++)] = i;  
        }
    }

    A->size = totalSize;
    return A;
}

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

void addSymToGrammar(char* tnt, LinkedListPtr* grammar, int gIndex) {
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

    if(grammar[gIndex]->head != NULL && data.type == NONTERM && data.nt == EPSILON) {
        nullable[grammar[gIndex]->head->data.nt] = 1;
    }
}

// @brief initializes the grammar rules by reading grammar.txt
void initGrammarRules() {
    grammar = (LinkedListPtr *) malloc(sizeof(LinkedListPtr) * NO_OF_RULES);
    int gIndex = 0;

    FILE* fp = fopen("grammar.txt", "ab");

    char tnt[MAX_SIZE_OF_TNT];
    memset(tnt, '\0', sizeof(tnt));

    grammar[0] = createLinkedList();
    int j = 0; // index on tnt
    while(1)
    {
        if(feof(fp)) break;
        char c = fgetc(fp);
        if(c == ' ') 
        {
            if(tnt[0] != '\0') // current string is not empty
            {
                addSymToGrammar(tnt, grammar, gIndex);
                memset(tnt, '\0', sizeof(tnt));
                j = 0;
            }
        }
        else if (c == '\n') 
        {
            if(tnt[0] != '\0') // current string is not empty
            {
                addSymToGrammar(tnt, grammar, gIndex);
                memset(tnt, '\0', sizeof(tnt));
                j = 0;
            }

            gIndex++;
            grammar[gIndex] = createLinkedList();
        }
        else if (c == '|') 
        {
            if(tnt[0] != '\0') // current string is not empty
            {
                addSymToGrammar(tnt, grammar, gIndex);
                memset(tnt, '\0', sizeof(tnt));
                j = 0;
            }
            
            gIndex++;
            grammar[gIndex] = createLinkedList();
            insertNode(grammar[gIndex], grammar[gIndex - 1]->head->data);
        } 
        else 
        {
            tnt[j++] = c;
        }

    }
}

token* first(SYM s) {
   
}

void computeFirstAndFollow() {

    // initialise first and follow set
    for(int i = 0; i < NO_OF_NONTERMS; i++) {
        firstSet[i] = (tokenSet) malloc(sizeof(TKSET));
        firstSet[i]->size = 0;

        followSet[i] = (tokenSet) malloc(sizeof(TKSET));
        followSet[i]->size = 0;
    }

    // calculate nullables
    nullable[EPSILON] = 1;
    for(int i = 0; i < NO_OF_RULES; i++) {
        NT nt = grammar[i]->head->data.nt;

        NodePtr curr = grammar[i]->head->next;
        int isNull = 1;
        while(curr != NULL) {
            if(curr->data.type == TERM) {
                isNull = 0;
                break;
            } else {
                isNull = isNull & (nullable[curr->data.nt]);
            }
        }
        nullable[nt] = isNull;
    }
}

