#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

// d, named according to convention for the transition function in DFAs, delta
// if state is in initState and current character is ch, take state to finState
#define d(initState, ch, finState)     \
    if (state == initState && c == ch) \
    {                                  \
        state = finState;              \
        continue;                      \
    }

// for checking if cond is satisfied (use c as char variable as defined in the function)
#define dr(initState, cond, finState) \
    if (state == initState && cond)   \
    {                                 \
        state = finState;             \
        continue;                     \
    }

// catchall case, to be used after all others are covered
#define dn(initState, finState) \
    if (state == initState)     \
    {                           \
        state = finState;       \
        continue;               \
    }

// shorthand for if, for accept states
#define case_(s) if (state == s)

char *filename;
twinBuffer B;
hashTable ht;

/// @brief initialize the lexer and populate the hashmap
void initLexer()
{

    ht = createEmptyHashTable();

    // populate the hashmap
    int k = insert(ht, "with", TK_WITH);         // with
    k = insert(ht, "parameters", TK_PARAMETERS); // parameters
    k = insert(ht, "end", TK_END);               // end
    k = insert(ht, "while", TK_WHILE);           // while
    k = insert(ht, "union", TK_UNION);           // union
    k = insert(ht, "endunion", TK_ENDUNION);     // end union
    k = insert(ht, "definetype", TK_DEFINETYPE); // definetype
    k = insert(ht, "as", TK_AS);                 // as
    k = insert(ht, "type", TK_TYPE);             // type
    k = insert(ht, "_main", TK_MAIN);            // main
    k = insert(ht, "global", TK_GLOBAL);         // global
    k = insert(ht, "parameter", TK_PARAMETER);   // parameter
    k = insert(ht, "list", TK_LIST);             // list
    k = insert(ht, "[", TK_SQL);                 // left sqr
    k = insert(ht, "]", TK_SQR);                 // right sqr
    k = insert(ht, "input", TK_INPUT);           // input
    k = insert(ht, "output", TK_OUTPUT);         //  output
    k = insert(ht, "int", TK_INT);               // int
    k = insert(ht, "real", TK_REAL);             // real
    k = insert(ht, ",", TK_COMMA);               // comma
    k = insert(ht, ";", TK_SEM);                 // semicolon
    k = insert(ht, ":", TK_COLON);               // colon
    k = insert(ht, ".", TK_DOT);                 // dot
    k = insert(ht, "endwhile", TK_ENDWHILE);     // endwhile
    k = insert(ht, "(", TK_OP);                  // (
    k = insert(ht, ")", TK_CL);                  // )
    k = insert(ht, "if", TK_IF);                 // if
    k = insert(ht, "then", TK_THEN);             // then
    k = insert(ht, "endif", TK_ENDIF);           // endif
    k = insert(ht, "read", TK_READ);             // read
    k = insert(ht, "write", TK_WRITE);           // write
    k = insert(ht, "return", TK_RETURN);         // return
    k = insert(ht, "+", TK_PLUS);                // plus
    k = insert(ht, "-", TK_MINUS);               // minus
    k = insert(ht, "*", TK_MUL);                 // mul
    k = insert(ht, "/", TK_DIV);                 // div
    k = insert(ht, "call", TK_CALL);             // call
    k = insert(ht, "record", TK_RECORD);         // record
    k = insert(ht, "endrecord", TK_ENDRECORD);   // endrecord
    k = insert(ht, "else", TK_ELSE);             // else
    k = insert(ht, "&&&", TK_AND);               // and
    k = insert(ht, "@@@", TK_OR);                // or
    k = insert(ht, "~", TK_NOT);                 // not
    k = insert(ht, "<", TK_LT);                  // less than
    k = insert(ht, "<=", TK_LE);                 // less than eq to
    k = insert(ht, "==", TK_EQ);                 // equal to
    k = insert(ht, ">", TK_GT);                  // greater than
    k = insert(ht, ">=", TK_GE);                 // greater than eq to
    k = insert(ht, "!=", TK_NE);                 // not equal
}

/// @brief gives the token corresponding to string lex
/// @param lex
/// @return the token code
token get_token_code(char *lex)
{
    int ind = lookup(ht, lex);
    if (ind == -1)
    {
        switch (lex[0])
        {
        case '_':
            return TK_FUNID;

        case '#':
            return TK_RUID;

        default:
            return TK_FIELDID;
        }
    }

    return ht->items[ind]->val;
}

tokenInfo acceptState(token tk, twinBuffer B)
{
    return createTokenInfo(createPairLexemeToken(getLexeme(B), tk), B);
}

/// @brief returns true if the input is a symbol
int isSym(char c)
{
    char cptr[1];
    cptr[0] = c;

    if (lookup(ht, c) == -1)
        return 0;
    else
        return 1;
}

tokenInfo getNextToken()
{
    B = initBuffer(filename);

    int state = 0;
    char *lex;

    while (1)
    {
        char c = nextChar(B);

        d(0, '>', 8);
        d(0, '!', 11);
        d(8, '=', 9);
        d(0, '=', 48);
        d(0, '&', 13);
        d(0, '@', 16);
        if (isSym(c))
        {
            d(0, c, 19);
        }
        dn(11, 12);
        dn(8, 10);
        dn(48, 49);
        dn(13, 14);
        dn(14, 15);
        dn(16, 17);
        dn(17, 18);

        case_(9)
        {
            return acceptState(TK_GE, B);
        }

        case_(10)
        {
            retract(B);
            return acceptState(TK_GT, B);
        }
        case_(12)
        {
            return acceptState(TK_NE, B);
        }
        case_(15)
        {
            return acceptState(TK_AND, B);
        }
        case_(18)
        {
            return acceptState(TK_OR, B);
        }
        case_(19)
        {
            return acceptState(get_token_code(lex), B);
        }
        case_(49)
        {
            return acceptState(TK_EQ, B);
        }
    }
}
