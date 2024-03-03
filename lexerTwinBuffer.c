#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

twinBuffer initBuffer(char *filename)
{
    twinBuffer B = (twinBuffer)malloc(sizeof(struct twinBuffer));

    if (!B)
        return NULL;

    B->beginBufferNo = 0;
    B->begin = B->buffer[B->beginBufferNo];

    B->forwardBufferNo = 1;
    B->forward = B->buffer[B->forwardBufferNo] + BUFLEN - 1;

    B->lineNo = 1;
    B->fp = fopen(filename, "ab");

    if (B->fp == NULL)
    {
        free(B);
        return NULL;
    }

    return B;
}

char nextChar(twinBuffer B)
{
    return *(advance(B)->forward);
}

twinBuffer reload(twinBuffer B)
{
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
        B->retractions--;

    return B;
}

twinBuffer retract(twinBuffer B)
{
    if (B->forward == B->buffer[B->forwardBufferNo])
    {
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
    B = advance(B);

    B->begin = B->forward;
    B->beginBufferNo = B->forwardBufferNo;

    return B;
}

char *getLexeme(twinBuffer B)
{
    int lexLength;
    if (B->beginBufferNo == B->forwardBufferNo)
    {
        lexLength = B->forward - B->begin;
    }
    else
    {
        lexLength = B->buffer[B->beginBufferNo] + BUFLEN - B->begin + B->forward - B->buffer[B->forwardBufferNo];
    }

    char *lexeme = (char *)malloc(sizeof(char) * (lexLength + 1));

    if (!lexeme)
        return NULL;

    char *ptr = lexeme;
    for (char *ch = B->begin; ch != B->forward; ch++)
        *ptr++ = *ch;

    *ptr = '\0';

    return lexeme;
}
