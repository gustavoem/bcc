CFLAGS=-Wall -g
LDFLAGS= -lglut -lGLU -lGL

sphere: sphere.o
	gcc $(CFLAGS) sphere.o -o bola $(LDFLAGS)
sphere.o: enemyRender.c
	gcc $(CFLAGS) -c enemyRender.c -o sphere.o $(LDFLAGS)
clean: 
	rm -f *.o
