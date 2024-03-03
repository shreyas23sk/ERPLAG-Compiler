#ifndef PARSERDEF
#define PARSERDEF
#include "parserDef.h"
#endif
#include "lexer.h"

#define NO_OF_RULES 96
#define MAX_SIZE_OF_TNT 26
#define NO_OF_TERMS 57
#define NO_OF_NONTERMS 56

typedef struct
{
    token *set;
    int eps;
    int endOfInput;
    int size;
} TKSET;
typedef TKSET *tokenSet;

LinkedListPtr *grammar;
tokenSet firstSet[NO_OF_NONTERMS];
tokenSet followSet[NO_OF_NONTERMS];
int LLParseTable[NO_OF_NONTERMS][NO_OF_TERMS] = {{-1}};

void printTokenSet(tokenSet ts)
{
    for (int i = 0; i < ts->size; i++)
    {
        printf("%s ", tokenToString(ts->set[i]));
    }
    printf("\n");
}

tokenSet addTokenToTokenSet(tokenSet S, token tk)
{
    if (S->size == 0)
    {
        S->set = (token *)malloc(sizeof(token));
        S->set[0] = tk;
        S->size++;
        return S;
    }
    else
    {
        S->set = (token *)realloc(S->set, S->size + 1);
        S->set[S->size] = tk;
        S->size++;
    }
}

// A = A union B if withEpsilon = 1
// A = A union B - {EPSILON} otherwise
tokenSet unionTokenSet(tokenSet A, tokenSet B, int withEpsilon)
{
    int inSetA[NO_OF_TERMS] = {0};
    int inSetB[NO_OF_TERMS] = {0};

    for (int i = 0; i < A->size; i++)
    {
        inSetA[A->set[i]] = 1;
    }

    for (int i = 0; i < B->size; i++)
    {
        inSetB[B->set[i]] = 1;
    }
    int noOfTokensToBeAddedToA = 0;
    for (int i = 0; i < NO_OF_TERMS; i++)
    {
        noOfTokensToBeAddedToA += (~inSetA[i] & inSetB[i]);
    }

    int totalSize = A->size + noOfTokensToBeAddedToA;

    if (noOfTokensToBeAddedToA > 0)
    {

        if (A->size != 0)
            A->set = (token *)realloc(A->set, totalSize);
        else
            A->set = (token *)malloc(sizeof(token) * totalSize);

        int j = 0;
        for (int i = 0; i < NO_OF_TERMS; i++)
        {
            if (~inSetA[i] & inSetB[i])
            {
                A->set[A->size + (j++)] = i;
            }
        }

        A->size = totalSize;
    }

    if (withEpsilon)
    {
        A->eps = (A->eps | B->eps);
    }

    A->endOfInput = (A->endOfInput | B->endOfInput);

    return A;
}

SYM createSYM(TNT type, char *str)
{
    SYM data;
    data.type = type;
    if (type == TERM)
    {
        data.tk = stringToToken(str);
    }
    else
    {
        data.nt = stringToNT(str);
    }
    return data;
}

void addSymToGrammar(char *tnt, LinkedListPtr *grammar, int gIndex)
{
    SYM data;
    if (tnt[0] == 'T')
    {
        data = createSYM(TERM, tnt);
    }
    else
    {
        data = createSYM(NONTERM, tnt);
    }
    insertNode(grammar[gIndex], data);
}

// @brief initializes the grammar rules by reading grammar.txt
void initGrammarRules()
{
    grammar = (LinkedListPtr *)malloc(sizeof(LinkedListPtr) * NO_OF_RULES);
    int gIndex = 0;

    FILE *fp = fopen("grammar.txt", "r");

    char tnt[MAX_SIZE_OF_TNT];
    memset(tnt, '\0', sizeof(tnt));

    grammar[0] = createLinkedList();
    int j = 0; // index on tnt
    while (1)
    {

        char c = fgetc(fp);
        if (c == ' ')
        {
            if (tnt[0] != '\0') // current string is not empty
            {
                addSymToGrammar(tnt, grammar, gIndex);
                memset(tnt, '\0', sizeof(tnt));
                j = 0;
            }
        }
        else if (c == '\r')
        {
            if (tnt[0] != '\0') // current string is not empty
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
            if (tnt[0] != '\0') // current string is not empty
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
            if (c != '\n')
                tnt[j++] = c;
        }

        if (feof(fp))
        {
            break;
        }
    }

    printf("Grammar successfully loaded.\n");
}

tokenSet first(SYM s)
{
    if (s.type == TERM)
    {
        tokenSet st = (tokenSet)malloc(sizeof(TKSET));
        st->set = (token *)malloc(sizeof(token));
        st->set[0] = s.tk;
        st->size = 1;
        st->endOfInput = 0;
        st->eps = 0;
        return st;
    }
    else
    {
        return firstSet[s.nt];
    }
}

int isEqual(tokenSet *setOld, tokenSet *setNew)
{
    for (int i = 0; i < NO_OF_NONTERMS; i++)
    {
        if (setOld[i]->size != setNew[i]->size ||
            setOld[i]->endOfInput != setOld[i]->endOfInput ||
            setOld[i]->eps != setOld[i]->eps)
            return 0;
    }
    return 1;
}

tokenSet computeFirstList(NodePtr rhs)
{
    tokenSet temp = (tokenSet)malloc(sizeof(TKSET));
    temp->size = 0;
    temp->endOfInput = 0;
    temp->eps = 0;

    while (rhs != NULL)
    {
        if (rhs->data.type == NONTERM && firstSet[rhs->data.nt]->eps == 1)
        {
            temp = unionTokenSet(temp, firstSet[rhs->data.nt], 0);
            rhs = rhs->next;
        }
        else if (rhs->data.type == TERM)
        {
            temp = unionTokenSet(temp, first(rhs->data), 1);
            break;
        }
        else
        {
            temp = unionTokenSet(temp, firstSet[rhs->data.nt], 0);
            break;
        }
    }

    return temp;
}

void deepCopy(tokenSet *A, tokenSet *B)
{
    for (int i = 0; i < NO_OF_NONTERMS; i++)
    {
        A[i]->set = (token *)malloc(sizeof(token) * B[i]->size);
        for (int j = 0; j < B[i]->size; j++)
        {
            A[i]->set[j] = B[i]->set[j];
        }
        A[i]->endOfInput = B[i]->endOfInput;
        A[i]->eps = B[i]->eps;
        A[i]->size = B[i]->size;
    }
}

void computeFirst()
{
    tokenSet firstSetOld[NO_OF_NONTERMS];

    for (int i = 0; i < NO_OF_NONTERMS; i++)
    {
        firstSetOld[i] = (tokenSet)malloc(sizeof(TKSET));
        firstSetOld[i]->eps = (i == EPSILON);
        firstSetOld[i]->endOfInput = 0;
        firstSetOld[i]->size = 0;
    }

    int j = 0;

    while (j == 0 || !isEqual(firstSetOld, firstSet))
    {
        j = 1;
        deepCopy(firstSetOld, firstSet);
        for (int i = 0; i < NO_OF_RULES; i++)
        {
            LinkedListPtr pi = grammar[i];
            firstSet[pi->head->data.nt] = unionTokenSet(firstSet[pi->head->data.nt], computeFirstList(pi->head->next), 1);
        }
    }
    /*
    for(int i = 0; i < NO_OF_NONTERMS; i++) {
        printf("%s :- ", NTtoString(i));
        printTokenSet(firstSet[i]);
    } */
}

void computeFollow()
{
    tokenSet followSetOld[NO_OF_NONTERMS];

    int j = 0;
    while (j == 0 || !isEqual(followSetOld, followSet))
    {
        j++;
        deepCopy(followSetOld, followSet);
        for (int i = 0; i < NO_OF_RULES; i++)
        {
            NodePtr rhs = grammar[i]->head->next;

            while (rhs != NULL)
            {
                SYM data = rhs->data;
                tokenSet firstOfRemainingList = computeFirstList(rhs->next);

                if (data.type == NONTERM)
                {
                    followSet[data.nt] = unionTokenSet(followSet[data.nt], firstOfRemainingList, 0);
                }

                if (firstOfRemainingList->eps == 1)
                {
                    followSet[data.nt] = unionTokenSet(followSet[data.nt], followSet[grammar[i]->head->data.nt], 1);
                }

                rhs = rhs->next;
            }
        }
    }
    return;
}

tokenSet computePredict(LinkedListPtr production)
{
    tokenSet temp = computeFirstList(production->head->next);

    if (temp->eps == 1)
    {
        temp = unionTokenSet(temp, followSet[production->head->data.nt], 1);
    }

    temp->eps = 0;

    return temp;
}

void computeFirstAndFollow()
{

    // initialise first and follow set
    for (int i = 0; i < NO_OF_NONTERMS; i++)
    {
        firstSet[i] = (tokenSet)malloc(sizeof(TKSET));
        firstSet[i]->eps = (i == EPSILON);
        firstSet[i]->endOfInput = 0;
        firstSet[i]->size = 0;

        followSet[i] = (tokenSet)malloc(sizeof(TKSET));
        followSet[i]->eps = 0;
        followSet[i]->endOfInput = (i == program);
        followSet[i]->size = 0;
    }

    // computeFirst
    computeFirst();
    computeFollow();
    printf("Computed First and Follow Set\n");

    int isLL1 = 1;

    for (int i = 0; i < NO_OF_NONTERMS; i++)
    {
        for (int j = 0; j < NO_OF_TERMS; j++)
        {
            LLParseTable[i][j] = -1;
        }
    }

    // generate LLParseTable
    for (int i = 0; i < NO_OF_RULES; i++)
    {
        tokenSet s = computePredict(grammar[i]);

        NT nt = grammar[i]->head->data.nt;

        for (int j = 0; j < s->size; j++)
        {
            if (LLParseTable[nt][s->set[j]] != -1)
            {
                printf("%s %s %d\n", NTtoString(nt), tokenToString(s->set[j]), LLParseTable[nt][s->set[j]]);
            }
            LLParseTable[nt][s->set[j]] = i;
        }
    }

    printf("%d\n", isLL1);
}

ParseTreePtr parseInputSourceCode(char *testCaseFileName)
{
    initLexer(testCaseFileName);

    StackPtr stack = createStack();
    push(stack, createParseNode(createSYM(NONTERM, "program")));

    ParseTreePtr result = createParseTree();

    // algorithm adapted from TB Ch4.4, pg 227
    tokenInfo a = getNextToken();
    SYM X = (peek(stack))->val;

    while (X.tk != -1)
    {
        if ((X.type == TERM && X.tk == a->plt->val))
        {
            pop(stack);
            a = getNextToken();
        }
        else if (X.type == NONTERM && X.nt == EPSILON)
        {
            pop(stack);
        }
        else if (X.type == TERM)
        {
            printf("Encountered error during parsing!\n");
            break;
        }
        else if (LLParseTable[X.nt][a->plt->val] < 0)
        {
            printf("Encountered error during parsing!\n");
            break;
        }
        else
        {
            LinkedListPtr production = grammar[LLParseTable[X.nt][a->plt->val]];
            printList(production);

            ParseNodePtr top = pop(stack);

            if (result->root == NULL)
            {
                result->root = top;
            }

            NodePtr derivation = production->tail;
            while (derivation->prev != production->head)
            {
                ParseNodePtr newNode = createParseNode(derivation->data);
                push(stack, newNode);
                addChild(top, newNode);
                derivation = derivation->prev;
            }
        }
        X = peek(stack)->val;
    }

    return result;
}

int main()
{
    initGrammarRules();
    /*
    for(int i = 0; i < NO_OF_RULES; i++) {
        printf("%d :- ", i);
        printList(grammar[i]);
    } */

    computeFirstAndFollow();
}
