// TB Ch3 Pg 141
/*
    1. Pointer lexemeBegin, marks the beginning of the current lexeme, whose
    extent we are attempting to determine

    2. Pointer forward scans ahead until a pattern match is found; the exact
    strategy whereby this determination is made will be covered in the balance
    of this chapter

*/

#define BUFLEN 2048
#include <stdlib.h>
#include <stdio.h>

struct twinBuffer {
    FILE *fp;
    char buffer[2][BUFLEN];
    char* begin;
    char* forward;
    int forwardBufferNo, beginBufferNo; 
    int retractions;
};

typedef struct twinBuffer* twinBuffer;

twinBuffer initBuffer(char*);
char nextChar(twinBuffer); // advance buffer and return char, returns eof on completion of input
twinBuffer reload(twinBuffer);
twinBuffer advance(twinBuffer);
twinBuffer retract(twinBuffer);
twinBuffer resetBegin(twinBuffer);
