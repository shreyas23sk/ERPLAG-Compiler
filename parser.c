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
    int eps;
    int endOfInput;
    int size;
} TKSET;
typedef TKSET* tokenSet;

LinkedListPtr* grammar;
int nullable[NO_OF_NONTERMS];
tokenSet firstSet[NO_OF_NONTERMS];
tokenSet followSet[NO_OF_NONTERMS];
int LLParseTable[NO_OF_NONTERMS][NO_OF_TERMS];

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

    if(withEpsilon) {
        A->eps = (A->eps | B->eps);
    }

    A->endOfInput = (A->endOfInput | B->endOfInput);

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

tokenSet first(SYM s) {
    if(s.type == TERM) {
        tokenSet st = (tokenSet) malloc(sizeof(TKSET));
        st->set[0] = s.tk;
        return st;
    } else {
        return firstSet[s.nt];
    }
}

int isEqual(tokenSet* setOld, tokenSet* setNew) {
    for(int i = 0; i < NO_OF_NONTERMS; i++) {
        if(setOld[i]->size != setNew[i]->size || 
        setOld[i]->endOfInput != setOld[i]->endOfInput ||
        setOld[i]->eps != setOld[i]->eps)  return 0; 
    }
    return 1;
}

tokenSet computeFirstList(NodePtr rhs) {
    tokenSet temp = (tokenSet) malloc(sizeof(TKSET));
    temp->size = 0;
    temp->endOfInput = 0;
    temp->eps = 0;

    while(rhs != NULL) 
    {
        if(rhs->data.type == NONTERM && firstSet[rhs->data.nt]->eps == 1) {
            temp = unionTokenSet(temp, firstSet[rhs->data.nt], 0);
            rhs = rhs->next;
        } else if(rhs->data.type == TERM) {
            temp = unionTokenSet(temp, first(rhs->data), 1);
            break;
        } else {
            temp = unionTokenSet(temp, firstSet[rhs->data.nt], 0);
            break;
        }
    } 

    return temp;
}

void deepCopy(tokenSet* A, tokenSet* B) {
    for(int i = 0; i < NO_OF_NONTERMS; i++) {
        A[i]->set = (token *) malloc(sizeof(token) * B[i]->size);
        for(int j = 0; j < B[i]->size; j++) {
            A[i]->set[j] = B[i]->set[j];
        }
        A[i]->endOfInput = B[i]->endOfInput;
        A[i]->eps = B[i]->eps;
        A[i]->size = B[i]->size;
    }
}

void computeFirst() {
    tokenSet firstSetOld[NO_OF_NONTERMS];

    while(!isEqual(firstSetOld, firstSet)) 
    {
        deepCopy(firstSetOld, firstSet);
        for(int i = 0; i < NO_OF_RULES; i++) 
        {
            LinkedListPtr pi = grammar[i];
            firstSet[pi->head->data.nt] = unionTokenSet(firstSet[pi->head->data.nt], computerFirstList(pi->head->next), 1);
        }
    }
}

void computeFollow() {
    tokenSet followSetOld[NO_OF_NONTERMS];
    
    while(!isEqual(followSetOld, followSet)) 
    {
        for(int i = 0; i < NO_OF_RULES; i++) 
        {
            NodePtr rhs = grammar[i]->head->next;

            while(rhs != NULL) 
            {
                SYM data = rhs->data;
                tokenSet firstOfRemainingList = computeFirstList(rhs->next);
                
                if(data.type == NONTERM) 
                {
                    followSet[data.nt] = unionTokenSet(followSet[data.nt], firstOfRemainingList, 0);
                }
                
                if(firstOfRemainingList->eps == 1) 
                {
                    followSet[data.nt] = unionTokenSet(followSet[data.nt], followSet[grammar[i]->head->data.nt], 1);
                }
            }
        }
    }
    return ;
}

tokenSet computePredict(LinkedListPtr production) {
    tokenSet temp = computeFirstList(production->head->next);

    if(temp->eps == 1) 
    {
        temp = unionTokenSet(temp, followSet[production->head->data.nt], 1);
    }

    temp->eps = 0;

    return temp;
}

void computeFirstAndFollow() {

    // initialise first and follow set
    for(int i = 0; i < NO_OF_NONTERMS; i++) {
        firstSet[i] = (tokenSet) malloc(sizeof(TKSET));
        firstSet[i]->eps = (i == EPSILON);
        firstSet[i]->endOfInput = 0;
        firstSet[i]->size = 0;

        followSet[i] = (tokenSet) malloc(sizeof(TKSET));
        followSet[i]->eps = 0;
        followSet[i]->endOfInput = (i == program);
        followSet[i]->size = 0;
    }

    // computeFirst 
    computeFirst();

    // computeFollow
    computeFollow();
    
    // generate LLParseTable
    for(int i = 0; i < NO_OF_RULES; i++) {
        tokenSet s = computePredict(grammar[i]);

        NT nt = grammar[i]->head->data.nt;

        for(int j = 0; j < s->size; j++) {
            LLParseTable[nt][s->set[j]] = i;
        }
    }


}

