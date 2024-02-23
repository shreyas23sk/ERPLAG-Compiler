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
hashTable ht;

void initLexer() {

    ht = createEmptyHashTable();


// populate the hashmap
    int k = insert(ht,createPairLexemeToken("with",TK_WITH)); //with
    k = insert(ht,createPairLexemeToken("parameters",TK_PARAMETERS)); // parameters
    k = insert(ht,createPairLexemeToken("end",TK_END)); // end
    k = insert(ht,createPairLexemeToken("while",TK_WHILE)); // while
    k = insert(ht,createPairLexemeToken("union",TK_UNION)); // union
    k = insert(ht,createPairLexemeToken("endunion",TK_ENDUNION)); // end union
    k = insert(ht,createPairLexemeToken("definetype",TK_DEFINETYPE)); //definetype
    k = insert(ht,createPairLexemeToken("as",TK_AS)); // as
    k = insert(ht,createPairLexemeToken("type",TK_TYPE)); //type
    k = insert(ht,createPairLexemeToken("_main",TK_MAIN)); // main
    k = insert(ht,createPairLexemeToken("global",TK_GLOBAL)); //global
    k = insert(ht,createPairLexemeToken("parameter",TK_PARAMETER)); //parameter
    k = insert(ht,createPairLexemeToken("list",TK_LIST)); // list
    k = insert(ht,createPairLexemeToken("[",TK_SQL)); // left sqr
    k = insert(ht,createPairLexemeToken("]",TK_SQR)); // right sqr
    k = insert(ht,createPairLexemeToken("input",TK_INPUT)); // input
    k = insert(ht,createPairLexemeToken("output",TK_OUTPUT)); //  output
    k = insert(ht,createPairLexemeToken("int",TK_INT)); // int
    k = insert(ht,createPairLexemeToken("real",TK_REAL)); // real 
    k = insert(ht,createPairLexemeToken(",",TK_COMMA)); // comma 
    k = insert(ht,createPairLexemeToken(";",TK_SEM)); // semicolon
    k = insert(ht,createPairLexemeToken(":",TK_COLON)); // colon 
    k = insert(ht,createPairLexemeToken(".",TK_DOT)); // dot
    k = insert(ht,createPairLexemeToken("endwhile",TK_ENDWHILE)); // endwhile
    k = insert(ht,createPairLexemeToken("(",TK_OP)); // (
    k = insert(ht,createPairLexemeToken(")",TK_CL)); // )
    k = insert(ht,createPairLexemeToken("if",TK_IF)); // if
    k = insert(ht,createPairLexemeToken("then",TK_THEN)); // then
    k = insert(ht,createPairLexemeToken("endif",TK_ENDIF)); //endif
    k = insert(ht,createPairLexemeToken("read",TK_READ));// read
    k = insert(ht,createPairLexemeToken("write",TK_WRITE)); //write
    k = insert(ht,createPairLexemeToken("return",TK_RETURN));// return 
    k = insert(ht,createPairLexemeToken("+",TK_PLUS)); //plus
    k = insert(ht,createPairLexemeToken("-",TK_MINUS)); // minus
    k = insert(ht,createPairLexemeToken("*",TK_MUL)); //mul
    k = insert(ht,createPairLexemeToken("/",TK_DIV)); // div
    k = insert(ht,createPairLexemeToken("call",TK_CALL)); //call
    k = insert(ht,createPairLexemeToken("record",TK_RECORD)); //record
    k = insert(ht,createPairLexemeToken("endrecord",TK_ENDRECORD)); //endrecord
    k = insert(ht,createPairLexemeToken("else",TK_ELSE)); // else
    k = insert(ht,createPairLexemeToken("&&&",TK_AND)); // and
    k = insert(ht,createPairLexemeToken("@@@",TK_OR)); // or
    k = insert(ht,createPairLexemeToken("~",TK_NOT)); // not
    k = insert(ht,createPairLexemeToken("<",TK_LT)); // less than
    k = insert(ht,createPairLexemeToken("<=",TK_LE)); // less than eq to
    k = insert(ht,createPairLexemeToken("==",TK_EQ)); //equal to
    k = insert(ht,createPairLexemeToken(">",TK_GT)); // greater than
    k = insert(ht,createPairLexemeToken(">=",TK_GE)); // greater than eq to
    k = insert(ht,createPairLexemeToken("!=",TK_NE)); // not equal 
}

pairLexemeToken acceptState(token tk, twinBuffer B)
{
    return createPairLexemeToken(getLexeme(B), tk);
}

pairLexemeToken getNextToken()
{
    B = initBuffer(filename);
    int state = 0;
    char *lex;
    while (1)
    {
        char c = nextChar(B);
        switch (state)
        {
        case 0:
            switch (c)
            {
            case '>':
                state = 8;
                break;
            }
            break;
        case 8:
            switch (c)
            {
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

/// @brief gives the token corresponding to string lex 
/// @param lex
/// @return the token code
token get_token_code(char *lex){
    int ind = lookup(ht,lex);
    if(ind == -1){
        if(lex[0] == '_'){
            return TK_FUNID;
        }
        else if(lex[0] == '#'){
            return TK_RUID;
        }
        return TK_FIELDID;
    }
    return ht->items[i]->val;
}
