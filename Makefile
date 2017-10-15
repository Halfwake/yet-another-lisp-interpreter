lisp: eval.c parse.o tokenize.o
	gcc -Wall -g eval.c parse.o tokenize.o -std=c99 -o lisp

parse.o: parse.c parse.h tokenize.o
	gcc -Wall -g -c parse.c -std=c99

tokenize.o: tokenize.c tokenize.h
	gcc -Wall -g -c tokenize.c -std=c99
