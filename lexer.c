#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

#ifndef LEXER
#define LEXER
#include "lexer.h"
#endif

// Macro for setting state to FINAL if INITIAL is encountered and CONDN is satisfied
#define MOVE_IF(INITIAL, FINAL, CONDN) \
    if (state == INITIAL && (CONDN))   \
    {                                  \
        state = FINAL;                 \
        continue;                      \
    }

// Macro for setting state to FINAL if INITIAL is encountered
#define MOVE(INITIAL, FINAL) \
    if (state == INITIAL)    \
    {                        \
        state = FINAL;       \
        continue;            \
    }

// Shorthand for switch-case blocks
#define CASE(s) if (state == s)

char *fileName;
twinBuffer B;
hashTable ht;

// Initialize the lexer and populate the hashmap
void initLexer(char *testCaseFileName)
{
    fileName = testCaseFileName;
    B = initBuffer(fileName);

    ht = createHashTable();

    // Populate the hashmap
    insert(ht, "with", TK_WITH);
    insert(ht, "parameters", TK_PARAMETERS);
    insert(ht, "end", TK_END);
    insert(ht, "while", TK_WHILE);
    insert(ht, "union", TK_UNION);
    insert(ht, "endunion", TK_ENDUNION);
    insert(ht, "definetype", TK_DEFINETYPE);
    insert(ht, "as", TK_AS);
    insert(ht, "type", TK_TYPE);
    insert(ht, "_main", TK_MAIN);
    insert(ht, "global", TK_GLOBAL);
    insert(ht, "parameter", TK_PARAMETER);
    insert(ht, "list", TK_LIST);
    insert(ht, "[", TK_SQL);
    insert(ht, "]", TK_SQR);
    insert(ht, "input", TK_INPUT);
    insert(ht, "output", TK_OUTPUT);
    insert(ht, "int", TK_INT);
    insert(ht, "real", TK_REAL);
    insert(ht, ",", TK_COMMA);
    insert(ht, ";", TK_SEM);
    insert(ht, ":", TK_COLON);
    insert(ht, ".", TK_DOT);
    insert(ht, "endwhile", TK_ENDWHILE);
    insert(ht, "(", TK_OP);
    insert(ht, ")", TK_CL);
    insert(ht, "if", TK_IF);
    insert(ht, "then", TK_THEN);
    insert(ht, "endif", TK_ENDIF);
    insert(ht, "read", TK_READ);
    insert(ht, "write", TK_WRITE);
    insert(ht, "return", TK_RETURN);
    insert(ht, "+", TK_PLUS);
    insert(ht, "-", TK_MINUS);
    insert(ht, "*", TK_MUL);
    insert(ht, "/", TK_DIV);
    insert(ht, "call", TK_CALL);
    insert(ht, "record", TK_RECORD);
    insert(ht, "endrecord", TK_ENDRECORD);
    insert(ht, "else", TK_ELSE);
    insert(ht, "&&&", TK_AND);
    insert(ht, "@@@", TK_OR);
    insert(ht, "~", TK_NOT);
    insert(ht, "<", TK_LT);
    insert(ht, "<=", TK_LE);
    insert(ht, "==", TK_EQ);
    insert(ht, ">", TK_GT);
    insert(ht, ">=", TK_GE);
    insert(ht, "!=", TK_NE);
}

/// @brief gives the token corresponding to string lex
/// @param lex
/// @return token code for the lex
token getTokenCode(char *lex)
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

// Create token information for an accepted state
tokenInfo acceptState(token tk, twinBuffer B)
{
    return createTokenInfo(createPairLexemeToken(getLexeme(B), tk), B);
}

// Check if the input is a symbol
int isSym(char c)
{
    return lookup(ht, &c) != -1;
}

// Get the next token from the input
tokenInfo getNextToken()
{
    char *lex;
    int state = 0;

    while (1)
    {
        char c = nextChar(B);

        // DFA Implementation
        MOVE_IF(0, 19, isSym(c));

        MOVE_IF(0, 16, c == '@');
        MOVE(16, 17);
        MOVE(17, 18);

        MOVE_IF(0, 13, c == '&');
        MOVE(13, 14);
        MOVE(14, 15);

        MOVE_IF(0, 11, c == '!');
        MOVE(11, 12);

        MOVE_IF(0, 8, c == '>');
        MOVE_IF(8, 9, c == '=');
        MOVE(8, 10);

        MOVE_IF(0, 48, c == '=');
        MOVE(48, 49);

        // Return cases
        CASE(9)
        return acceptState(TK_GE, B);

        CASE(10)
        {
            retract(B);
            return acceptState(TK_GT, B);
        }

        CASE(12)
        return acceptState(TK_NE, B);

        CASE(15)
        return acceptState(TK_AND, B);

        CASE(18)
        return acceptState(TK_OR, B);

        CASE(19)
        return acceptState(getTokenCode(lex), B);

        CASE(49)
        return acceptState(TK_EQ, B);
    }
}
