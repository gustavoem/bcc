CFLAGS=-Wall --ansi -g
LDFLAGS= -lglut -lGLU -lGL -lm

all: cenario
	./cenario

cenario: cenario.o nave.o torre.o
	gcc $(CFLAGS) cenario.o	nave.o torre.o -o cenario $(LDFLAGS)
nave.o: nave.c GLnave.inc
	gcc $(CFLAGS) -c nave.c
dist:
	zip exemplo.zip *.c *.h *.inc *.ppm Makefile


clean:
	rm *.o *~ cenario
