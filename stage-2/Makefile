#	Authors:
#		- Gabriel Pakulski da Silva - 00274701
#		- Lucas Sonntag Hagen       - 00274698

CC=gcc
CFLAGS=-lfl -lm
ETAPA=etapa2

bison: parser.y
	bison -d parser.y
	flex  -o scanner.yy.c scanner.l
	${CC} -c -o scanner.o scanner.yy.c
	${CC} -c -o parser.o parser.tab.c
	${CC} -o main.out scanner.o parser.o main.c ${CFLAGS}
clean:
	rm -rf *.out *.o *.yy.c *.out.c *.tab.c *.tab.h *.yy.c
