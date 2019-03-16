CC=gcc
CFLAGS=-lfl -lm

scanner: scanner.l
	flex  -o scanner.c scanner.l
	${CC} -c -o scanner.o scanner.c
	${CC} -c -o main.o main.c
	${CC} -o scanner.out scanner.o ${CFLAGS}
	${CC} -o main.out scanner.o main.o ${CFLAGS}
clean:
	rm -rf scanner.out scanner.o scanner.c main.out main.o
