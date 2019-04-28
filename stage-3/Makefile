#	Authors:
#		- Gabriel Pakulski da Silva - 00274701
#		- Lucas Sonntag Hagen       - 00274698

CC=gcc
CFLAGS=-lfl -lm
ETAPA=etapa3

bison: parser.y
	bison -d parser.y
	flex  -o scanner.yy.c scanner.l
	${CC} -c scanner.yy.c parser.tab.c tree.c
	${CC} -o ${ETAPA} scanner.yy.o parser.tab.o tree.o main.c ${CFLAGS}
clean:
	rm -rf *.out *.o *.yy.c *.out.c *.tab.c *.tab.h *.yy.c ${ETAPA}
