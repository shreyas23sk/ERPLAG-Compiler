lexerCompiler:
	gcc -c lexerTwinBuffer.c lexerHashTable.c lexerPairLexemeToken.c lexerTokenInfo.c lexer.c stringNTConvert.c stringTokenConvert.c
	gcc -c linkedList.c 
	gcc -c stack.c 
	gcc -c parseTree.c 
	gcc -c parser.c 
	gcc -c driver.c
	gcc -o stage1exe stringNTConvert.o stringTokenConvert.o lexer.o lexerTwinBuffer.o lexerHashTable.o lexerPairLexemeToken.o lexerTokenInfo.o linkedList.o stack.o parseTree.o parser.o driver.o