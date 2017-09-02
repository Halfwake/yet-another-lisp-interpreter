a.out: parse.c parse.h tokenize.o
	gcc parse.c tokenize.o -std=c99

tokenize.o: tokenize.c tokenize.h
	gcc -c tokenize.c -std=c99
