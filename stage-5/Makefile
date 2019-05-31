#	Authors:
#		- Gabriel Pakulski da Silva - 00274701
#		- Lucas Sonntag Hagen       - 00274698

CC=gcc
CFLAGS=-lfl -lm -I include
ETAPA=etapa5

all:
	bison -d parser.y
	flex  -o scanner.yy.c scanner.l
	$(CC) *.c src/*.c -o $(ETAPA) $(CFLAGS)

clean:
	rm -rf *.out *.o *.yy.c *.out.c *.tab.c *.tab.h *.yy.c *.h.gch include/*.h.gch $(ETAPA)
