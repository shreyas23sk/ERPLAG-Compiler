#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

char nextChar(twinBuffer B)
{
    return *(advance(B)->forward);
}

twinBuffer initBuffer(char *filename)
{
    twinBuffer B = (twinBuffer)malloc(sizeof(struct twinBuffer));

    B->beginBufferNo = 0;
    B->begin = B->buffer[B->beginBufferNo];

    B->forwardBufferNo = 1;
    B->forward = B->buffer[B->forwardBufferNo] + BUFLEN - 1;

    B->fp = fopen(filename, "ab");

    return B;
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
        B->forward = B->forward--;
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
}