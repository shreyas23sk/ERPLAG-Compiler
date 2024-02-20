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
hashTable ht = createEmptyHashTable();


// populate the hashmap
int k = insert(ht,pairLexemeToken("with",TK_WITH)); //with
k = insert(ht,pairLexemeToken("parameters",TK_PARAMETERS)); // parameters
k = insert(ht,pairLexemeToken("end",TK_END)); // end
k = insert(ht,pairLexemeToken("while",TK_WHILE)); // while
k = insert(ht,pairLexemeToken("union",TK_UNION)); // union
k = insert(ht,pairLexemeToken("endunion",TK_ENDUNION)); // end union
k = insert(ht,pairLexemeToken("definetype",TK_DEFINETYPE)); //definetype
k = insert(ht,pairLexemeToken("as",TK_AS)); // as
k = insert(ht,pairLexemeToken("type",TK_TYPE)); //type
k = insert(ht,pairLexemeToken("_main",TK_MAIN)); // main
k = insert(ht,pairLexemeToken("global",TK_GLOBAL)); //global
k = insert(ht,pairLexemeToken("parameter",TK_PARAMETER)); //parameter
k = insert(ht,pairLexemeToken("list",TK_LIST)); // list
k = insert(ht,pairLexemeToken("[",TK_SQL)); // left sqr
k = insert(ht,pairLexemeToken("]",TK_SQR)); // right sqr
k = insert(ht,pairLexemeToken("input",TK_INPUT)); // input
k = insert(ht,pairLexemeToken("output",TK_OUTPUT)); //  output
k = insert(ht,pairLexemeToken("int",TK_INT)); // int
k = insert(ht,pairLexemeToken("real",TK_REAL)); // real 
k = insert(ht,pairLexemeToken(",",TK_COMMA)); // comma 
k = insert(ht,pairLexemeToken(";",TK_SEM)); // semicolon
k = insert(ht,pairLexemeToken(":",TK_COLON)); // colon 
k = insert(ht,pairLexemeToken(".",TK_DOT)); // dot
k = insert(ht,pairLexemeToken("endwhile",TK_ENDWHILE)); // endwhile
k = insert(ht,pairLexemeToken("(",TK_OP)); // (
k = insert(ht,pairLexemeToken(")",TK_CL)); // )
k = insert(ht,pairLexemeToken("if",TK_IF)); // if
k = insert(ht,pairLexemeToken("then",TK_THEN)); // then
k = insert(ht,pairLexemeToken("endif",TK_ENDIF)); //endif
k = insert(ht,pairLexemeToken("read",TK_READ));// read
k = insert(ht,pairLexemeToken("write",TK_WRITE)); //write
k = insert(ht,pairLexemeToken("return",TK_RETURN));// return 
k = insert(ht,pairLexemeToken("+",TK_PLUS)); //plus
k = insert(ht,pairLexemeToken("-",TK_MINUS)); // minus
k = insert(ht,pairLexemeToken("*",TK_MUL)); //mul
k = insert(ht,pairLexemeToken("/",TK_DIV)); // div
k = insert(ht,pairLexemeToken("call",TK_CALL)); //call
k = insert(ht,pairLexemeToken("record",TK_RECORD)); //record
k = insert(ht,pairLexemeToken("endrecord",TK_ENDRECORD)); //endrecord
k = insert(ht,pairLexemeToken("else",TK_ELSE)); // else
k = insert(ht,pairLexemeToken("&&&",TK_AND)); // and
k = insert(ht,pairLexemeToken("@@@",TK_OR)); // or
k = insert(ht,pairLexemeToken("~",TK_NOT)); // not
k = insert(ht,pairLexemeToken("<",TK_LT)); // less than
k = insert(ht,pairLexemeToken("<=",TK_LE)); // less than eq to
k = insert(ht,pairLexemeToken("==",TK_EQ)); //equal to
k = insert(ht,pairLexemeToken(">",TK_GT)); // greater than
k = insert(ht,pairLexemeToken(">=",TK_GE)); // greater than eq to
k = insert(ht,pairLexemeToken("!=",TK_NE)); // not equal 

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
