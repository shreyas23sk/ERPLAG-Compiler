#ifndef LEXERDEF
#define LEXERDEF
#include "lexerDef.h"
#endif

#ifndef LEXER
#define LEXER
#include "lexer.h"
#endif

// Set INITIAL state to FINAL if CONDN is satisfied
#define MOVE_IF(INITIAL, FINAL, CONDN) \
    if (state == INITIAL && (CONDN))   \
    {                                  \
        state = FINAL;                 \
        continue;                      \
    }

// Set INITIAL state to FINAL and continue
#define MOVE(INITIAL, FINAL) \
    if (state == INITIAL)    \
    {                        \
        state = FINAL;       \
        continue;            \
    }

/// @brief Check if the state is equal to s
#define CASE(s) if (state == s)

/// @brief Check if the input is equal to x
#define EQ(x) c == x

char *fileName;
twinBuffer B;
hashTable ht;

// Initialize the lexer and populate the hashmap
void initLexer(char *testCaseFileName)
{
    fileName = testCaseFileName;
    B = initBuffer(fileName);

    ht = createHashTable();

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

/// @brief Get the token code for the given lexeme
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

/// @brief Create token information for an accepted state
tokenInfo acceptState(token tk, twinBuffer B)
{
    return createTokenInfo(createPairLexemeToken(getLexeme(B), tk), B);
}

/// @brief Check if the input is a symbol
int isSymbol(char c)
{
    return lookup(ht, &c) != -1;
}

/// @brief Check if the input is an alphabet
int isAllAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/// @brief Check if the input is a lowercase alphabet
int isAlpha(char c)
{
    return c >= 'a' && c <= 'z';
}

/// @brief Check if the input is a variable alphabet (b, c, d)
int isVarAlpha(char c)
{
    return EQ('b') || EQ('c') || EQ('d');
}

/// @brief Check if the input is a non-variable alphabet
int isNonVarAlpha(char c)
{
    return isAllAlpha(c) && !isVarAlpha(c);
}

/// @brief Check if the input is a digit
int isDigit(char c)
{
    return c >= '0' && c <= '9';
}

/// @brief Check if the input is a variable digit (2 to 7)
int isVarDigit(char c)
{
    return c >= '2' && c <= '7';
}

/// @brief Check if the input is a non-variable digit
int isNonVarDigit(char c)
{
    return isDigit(c) && !isVarDigit(c);
}

/// @brief Check if the input is a blank space
int isBlank(char c)
{
    return EQ(' ') || EQ('\t');
}

/// @brief Get the next token from the input
tokenInfo getNextToken()
{
    char *lex;
    int state = 0;

    while (1)
    {
        char c = nextChar(B);

        // DFA Transitions
        MOVE_IF(0, 19, isSymbol(c));

        MOVE_IF(0, 16, EQ('@'));
        MOVE_IF(16, 17, EQ('@'));
        MOVE_IF(17, 18, EQ('@'));

        MOVE_IF(0, 13, EQ('&'));
        MOVE_IF(13, 14, EQ('&'));
        MOVE_IF(14, 15, EQ('&'));

        MOVE_IF(0, 48, EQ('='));
        MOVE_IF(48, 49, EQ('='));

        MOVE_IF(0, 11, EQ('!'));
        MOVE_IF(11, 12, EQ('='));

        MOVE_IF(0, 8, EQ('>'));
        MOVE_IF(8, 9, EQ('='));
        MOVE(8, 10);

        MOVE_IF(0, 1, EQ('<'));
        MOVE_IF(1, 2, EQ('-'));
        MOVE(1, 7);
        MOVE_IF(2, 3, EQ('-'));
        MOVE(2, 5);
        MOVE_IF(3, 4, EQ('-'));

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
        MOVE_IF(29, 30, EQ('.'));
        MOVE(29, 37);
        MOVE_IF(30, 31, isDigit(c));
        MOVE(30, 38);
        MOVE_IF(31, 32, isDigit(c));
        MOVE_IF(32, 33, EQ('E'));
        MOVE(32, 47);
        MOVE_IF(33, 34, EQ('+') || EQ('-'));
        MOVE_IF(33, 35, isDigit(c));
        MOVE_IF(34, 35, isDigit(c));
        MOVE_IF(35, 36, isDigit(c));

        MOVE_IF(0, 39, EQ('-'));
        MOVE_IF(39, 40, isAllAlpha(c));
        MOVE_IF(40, 40, isAllAlpha(c));
        MOVE_IF(40, 41, isDigit(c));
        MOVE(40, 42);
        MOVE_IF(41, 41, isDigit(c));
        MOVE(41, 42);

        MOVE_IF(0, 43, EQ('#'));
        MOVE_IF(43, 44, isAlpha(c));
        MOVE_IF(44, 44, isAlpha(c));
        MOVE(44, 45);

        MOVE_IF(0, 20, c == '%')
        MOVE_IF(0, 50, c == '\n');

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

        CASE(20)
        {
            return acceptState(TK_COMMENT, B);
        }

        CASE(50)
        {
            // INCREMENT THE LINE BUFFER
            B->lineNo++;
            MOVE(50, 0);
        }
    }
}


void removeComments(char *fileName, char *outputFileName)
{
    FILE *fp = fopen(fileName, "r");
    FILE *fp2 = fopen(outputFileName, "w");
    char c;
    int k = 0;

    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '%')
        {
            k = 1;
        }
        else if (c == '\n')
        {
            k = 0;
        }
        if (k == 0)
        {
            fputc(c, fp2);
        }
    }
    fclose(fp);
    fclose(fp2);
}
