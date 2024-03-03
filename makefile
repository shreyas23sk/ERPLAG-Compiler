lexerCompiler:
	gcc -c lexerTwinBuffer.c lexerHashTable.c lexerPairLexemeToken.c lexerTokenInfo.c lexer.c
	gcc -o lexer_exe lexer.o lexerTwinBuffer.o lexerHashTable.o lexerPairLexemeToken.o lexerTokenInfo.o
	./lexer