#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

// Macro for transition rules in DFAs
#define TRANSITION(initState, cond, finState) \
    if (state == initState && (cond))         \
    {                                         \
        state = finState;                     \
        continue;                             \
    }

// Macro for setting state to finState if initState is encountered
#define DEFAULT(initState, finState) \
    if (state == initState)          \
    {                                \
        state = finState;            \
        continue;                    \
    }

// Shorthand for switch-case blocks
#define CASE(s) if (state == s)

char *filename;
twinBuffer B;
hashTable ht;

/// @brief Initialize the lexer and populate the hashmap
void initLexer()
{
    ht = createEmptyHashTable();

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

// Create token information for an accepted state
tokenInfo acceptState(token tk, twinBuffer B)
{
    return createTokenInfo(createPairLexemeToken(getLexeme(B), tk), B);
}

/// @brief Check if the input is a symbol
int isSym(char c)
{
    return lookup(ht, &c) != -1;
}

/// @brief Get the next token from the input
tokenInfo getNextToken()
{
    B = initBuffer(filename);

    char *lex;
    int state = 0;

    while (1)
    {
        char c = nextChar(B);

        TRANSITION(0, c == '>', 8);
        TRANSITION(0, c == '!', 11);
        TRANSITION(8, c == '=', 9);
        TRANSITION(0, c == '=', 48);
        TRANSITION(0, c == '&', 13);
        TRANSITION(0, c == '@', 16);

        if (isSym(c))
            TRANSITION(0, 1, 19);

        DEFAULT(11, 12);
        DEFAULT(8, 10);
        DEFAULT(48, 49);
        DEFAULT(13, 14);
        DEFAULT(14, 15);
        DEFAULT(16, 17);
        DEFAULT(17, 18);

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
        return acceptState(get_token_code(lex), B);

        CASE(49)
        return acceptState(TK_EQ, B);
    }
}
