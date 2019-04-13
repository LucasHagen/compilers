#	Authors:
#		- Gabriel Pakulski da Silva - 00274701
#		- Lucas Sonntag Hagen       - 00274698

CC=gcc
CFLAGS=-lfl -lm
ETAPA=etapa1

scanner: scanner.l
	flex  -o scanner.yy.c scanner.l
	${CC} -c -o scanner.o scanner.yy.c
	${CC} -c -o main.o main.c
	${CC} -o scanner.out scanner.o ${CFLAGS}
	${CC} -o ${ETAPA} scanner.o main.o ${CFLAGS}
clean:
	rm -rf *.out *.o *.yy.c ${ETAPA}
