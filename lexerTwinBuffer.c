// Group No 37
// Shreyas Kumar 2021A7PS2432P
// Prateek Kashyap 2021A7PS1449P
// Harshith Vasireddy 2021A7PS0504P
// Yuvraj Doshi 2021A7PS2425P

#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

twinBuffer initBuffer(char *filename)
{
    twinBuffer B = (twinBuffer)malloc(sizeof(struct twinBuffer));

    if (!B)
        return NULL;
    
    for(int i = 0; i < BUFLEN; i++) 
    {
        B->buffer[0][i] = '\0';
        B->buffer[1][i] = '\0';
    }

    B->beginBufferNo = 0;
    B->begin = B->buffer[B->beginBufferNo];

    B->forwardBufferNo = 1;
    B->forward = B->buffer[B->forwardBufferNo] + BUFLEN - 1;

    B->lineNo = 1;
    B->fp = fopen(filename, "r");
    B->retractions = 0;


    return B;
}

char nextChar(twinBuffer B)
{
    return *(advance(B)->forward);
}

twinBuffer reload(twinBuffer B)
{
    for(int i = 0; i < BUFLEN; i++) 
    {
        B->buffer[B->forwardBufferNo][i] = '\0';
    }
    fread(B->buffer[B->forwardBufferNo], sizeof(char), BUFLEN, B->fp);
    return B;
}

twinBuffer advance(twinBuffer B)
{
    if (B->forward == B->buffer[B->forwardBufferNo] + BUFLEN - 1)
    {
        B->forwardBufferNo = !B->forwardBufferNo;
        B->forward = B->buffer[B->forwardBufferNo];

        if (!B->retractions)
            reload(B);
    }
    else
    {
        B->forward++;
    }

    if (B->retractions > 0)
    {
        B->retractions--;
    }

    return B;
}

twinBuffer retract(twinBuffer B)
{
    if (B->forward == B->buffer[B->forwardBufferNo])
    {
        printf("hello\n");
        B->forwardBufferNo = !B->forwardBufferNo;
        B->forward = B->buffer[B->forwardBufferNo] + BUFLEN - 1;
    }
    else
    {
        B->forward--;
    }

    B->retractions++;

    return B;
}

// advances forward beyond current lexeme and
// sets begin to be equal to forward

twinBuffer resetBegin(twinBuffer B)
{
    advance(B);
    B->begin = B->forward;
    B->beginBufferNo = B->forwardBufferNo;

    retract(B);

    return B;
}

char *getLexeme(twinBuffer B)
{
    int lexLength = 0;

    if (*B->begin == ' ')
        B->begin++;

    if (B->beginBufferNo == B->forwardBufferNo)
    {
        lexLength = B->forward - B->begin + 1;
        char* lexeme = (char *) malloc(sizeof(char) * (lexLength + 1));
        
        int i = 0;
        while (i < lexLength)
        {
            lexeme[i] = *(B->begin + i);
            i++;
        }
        lexeme[lexLength] = '\0';

        return lexeme;
    }
    else
    {
        int lexLength1 = B->buffer[B->beginBufferNo] + BUFLEN - B->begin;
        int lexLength2 = B->forward - B->buffer[B->forwardBufferNo] + 1;

        char *lexeme = (char *)malloc(sizeof(char) * (lexLength1 + lexLength2 + 1));

        int i = 0, j = 0;

        while (i < lexLength1)
        {
            lexeme[i] = *(B->begin + i);
            i++;
        }

        while (j < lexLength2)
        {
            lexeme[lexLength1 + j] = *(B->buffer[B->forwardBufferNo] + j);
            j++;
        }

        lexeme[lexLength1 + lexLength2] = '\0';
        printf("%d %d %s\n", lexLength1, lexLength2, lexeme);
        return lexeme;
    }
}
