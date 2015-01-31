CFLAGS=-Wall -g
LDFLAGS= -lglut -lGLU -lGL

box: mylittlebox.o
	gcc $(CFLAGS) mylittlebox.o -o box $(LDFLAGS)
mylittlebox.o:
	gcc $(CFLAGS) -c mylittlebox.c $(LDFLAGS)
clean: 
	rm -f *.o