CC=gcc
CFLAGS=-lfl -lm

bison: parser.y
	bison -d parser.y
	flex  -o scanner.out.c scanner.l
	${CC} -c -o scanner.o scanner.out.c
	${CC} -c -o parser.o parser.tab.c
	${CC} -o main.out scanner.o parser.o main.c ${CFLAGS}
clean:
	rm -rf *.out *.o *.out.c *.tab.c *.tab.h *.yy.c
