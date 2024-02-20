#ifndef LEXERHASHTABLE
#define LEXERHASHTABLE
#include "lexerHashTable.h"
#endif
#ifndef TWINBUFFER
#define TWINBUFFER
#include "lexerTwinBuffer.h"
#endif

char*  filename;
twinBuffer B;
// hashmap


pairLexemeToken acceptState(token tk, twinBuffer B) {
    return createPairLexemeToken(getLexeme(B), tk);
}

pairLexemeToken getNextToken() {
    B = initBuffer(filename);
    int state = 0;
    char* lex;
    while(1) {
        char c = nextChar(B);
        switch(state){
            case 0:
                switch(c) {
                    case '>': 
                        state = 8;
                        break;
                }
                break;
            case 8:
                switch(c) {
                    case '=':
                        state = 9;
                        break;
                    default:
                        state = 10;
                        break;
                }
                break;
            case 9:
                return acceptState(TK_GE, B);
            case 10:
                retract(B);
                return acceptState(TK_GT, B);
                
        }
    }
}
