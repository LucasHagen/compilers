#	Authors:
#		- Gabriel Pakulski da Silva - 00274701
#		- Lucas Sonntag Hagen       - 00274698

CC=gcc
CFLAGS=-lfl -lm
ETAPA=etapa2

bison: parser.y
	bison -d parser.y
	flex  scanner.l
	${CC} -c lex.yy.c parser.tab.c
	${CC} -o parser lex.yy.o parser.tab.o main.c ${CFLAGS}
clean:
	rm -rf *.out *.o *.yy.c *.out.c *.tab.c *.tab.h *.yy.c parser
