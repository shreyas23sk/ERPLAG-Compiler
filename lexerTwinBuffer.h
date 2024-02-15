// TB Ch3 Pg 141
/*
    1. Pointer lexemeBegin, marks the beginning of the current lexeme, whose
    extent we are attempting to determine

    2. Pointer forward scans ahead until a pattern match is found; the exact
    strategy whereby this determination is made will be covered in the balance
    of this chapter

*/

#define BUFLEN 2048

struct twinBuffer {
    char buffer[2][BUFLEN];
    char* lexemeBegin;
    char* forward;
    int whichBuffer; 
};

typedef struct twinBuffer twinBuffer;

twinBuffer initBuffer();
char nextChar(twinBuffer); // advance buffer and return char, returns eof on completion of input
twinBuffer advance(twinBuffer);
twinBuffer retract(twinBuffer);
