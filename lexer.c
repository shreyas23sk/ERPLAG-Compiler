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

// Check if the input is an alphabet
int isAllAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Check if the input is a lowercase alphabet
int isAlpha(char c)
{
    return c >= 'a' && c <= 'z';
}

// Check if the input is a variable alphabet (b, c, d)
int isVarAlpha(char c)
{
    return c == 'b' || c == 'c' || c == 'd';
}

// Check if the input is a non-variable alphabet
int isNonVarAlpha(char c)
{
    return isAllAlpha(c) && !isVarAlpha(c);
}

// Check if the input is a digit
int isDigit(char c)
{
    return c >= '0' && c <= '9';
}

// Check if the input is a variable digit (2 to 7)
int isVarDigit(char c)
{
    return c >= '2' && c <= '7';
}

// Check if the input is a non-variable digit
int isNonVarDigit(char c)
{
    return isDigit(c) && !isVarDigit(c);
}

// Check if the input is a blank space
int isBlank(char c)
{
    return c == ' ' || c == '\t';
}

// Get the next token from the input
tokenInfo getNextToken()
{
    char *lex;
    int state = 0;

    while (1)
    {
        char c = nextChar(B);

        // DFA Transitions
        MOVE_IF(0, 19, isSym(c));

        MOVE_IF(0, 16, c == '@');
        MOVE_IF(16, 17, c == '@');
        MOVE_IF(17, 18, c == '@');

        MOVE_IF(0, 13, c == '&');
        MOVE_IF(13, 14, c == '&');
        MOVE_IF(14, 15, c == '&');

        MOVE_IF(0, 48, c == '=');
        MOVE_IF(48, 49, c == '=');

        MOVE_IF(0, 11, c == '!');
        MOVE_IF(11, 12, c == '=');

        MOVE_IF(0, 8, c == '>');
        MOVE_IF(8, 9, c == '=');
        MOVE(8, 10);

        MOVE_IF(0, 1, c == '<');
        MOVE_IF(1, 2, c == '-');
        MOVE(1, 7);
        MOVE_IF(2, 3, c == '-');
        MOVE(2, 5);
        MOVE_IF(3, 4, c == '-');

        MOVE_IF(0, 23, isVarAlpha(c));
        MOVE_IF(23, 24, isVarDigit(c));
        MOVE_IF(23, 26, isAlpha(c));
        MOVE(23, 28);
        MOVE_IF(24, 24, isVarAlpha(c));
        MOVE_IF(24, 25, isVarDigit(c));
        MOVE(24, 26);
        MOVE_IF(25, 25, isVarDigit(c));
        MOVE(25, 26);

        MOVE_IF(0, 27, isNonVarAlpha(c));
        MOVE_IF(27, 27, isAlpha(c));
        MOVE(27, 28);

        MOVE_IF(0, 29, isDigit(c));
        MOVE_IF(29, 29, isDigit(c));
        MOVE_IF(29, 30, c == '.');
        MOVE(29, 37);
        MOVE_IF(30, 31, isDigit(c));
        MOVE(30, 38);
        MOVE_IF(31, 32, isDigit(c));
        MOVE_IF(32, 33, c == 'E');
        MOVE(32, 47);
        MOVE_IF(33, 34, c == '+' || c == '-');
        MOVE_IF(33, 35, isDigit(c));
        MOVE_IF(34, 35, isDigit(c));
        MOVE_IF(35, 36, isDigit(c));

        MOVE_IF(0, 39, c == '-');
        MOVE_IF(39, 40, isAllAlpha(c));
        MOVE_IF(40, 40, isAllAlpha(c));
        MOVE_IF(40, 41, isDigit(c));
        move(40, 42);
        MOVE_IF(41, 41, isDigit(c));
        MOVE(41, 42);

        MOVE_IF(0, 43, c == '#');
        MOVE_IF(43, 44, isAlpha(c));
        MOVE_IF(44, 44, isAlpha(c));
        MOVE(44, 45);

        // DFA Returns
        CASE(19)
        return acceptState(getTokenCode(lex), B);

        CASE(18)
        return acceptState(TK_OR, B);

        CASE(15)
        return acceptState(TK_AND, B);

        CASE(49)
        return acceptState(TK_EQ, B);

        CASE(12)
        return acceptState(TK_NE, B);

        CASE(9)
        return acceptState(TK_GE, B);

        CASE(10)
        {
            retract(B);
            return acceptState(TK_GT, B);
        }

        CASE(7)
        return acceptState(TK_LT, B);

        CASE(6)
        return acceptState(TK_LE, B);

        CASE(5)
        {
            retract(B);
            retract(B);
            return acceptState(TK_LT, B);
        }

        CASE(4)
        return acceptState(TK_ASSIGNOP, B);

        CASE(26)
        {
            retract(B);
            return acceptState(TK_ID, B);
        }

        CASE(28)
        {
            retract(B);
            return acceptState(getTokenCode(lex), B);
        }

        CASE(37)
        {
            retract(B);
            return acceptState(TK_NUM, B);
        }

        CASE(38)
        {
            retract(B);
            retract(B);
            return acceptState(TK_NUM, B);
        }

        CASE(36)
        return acceptState(TK_RNUM, B);

        CASE(47)
        {
            retract(B);
            return acceptState(TK_RNUM, B);
        }

        CASE(42)
        {
            retract(B);
            return acceptState(getTokenCode(lex), B);
        }

        CASE(45)
        {
            retract(B);
            return acceptState(TK_RUID, B);
        }
    }
}
