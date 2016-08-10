# variaveis que serao usadas como opcoes do gcc
CFLAGSa = -Wall -Wno-unused-result -ansi -O2 -pedantic -g
CFLAGSb = -Wall -O0
#    -ansi proibe comentarios com prefixo '//'
#    -g prepara o terreno para que o gdb possa caçar bugs

LIBRARIES = -lm
#    necessario no caso de usar math.h

main: main.o DIGRAPHlists.o
	gcc $(CFLAGSa) main.o DIGRAPHlists.o -lm -o main

lists: test_lists.o DIGRAPHlists.o
	gcc $(CFLAGSa) test_lists.o DIGRAPHlists.o -o test_lists

matrix: test_matrix.o DIGRAPHmatrix.o
	gcc $(CFLAGSa) test_matrix.o DIGRAPHmatrix.o -o test_matrix

test_matrix.o: test_matrix.c DIGRAPHmatrix.h
	gcc $(CFLAGSa) -c test_matrix.c

test_lists.o: test_lists.c DIGRAPHlists.h
	gcc $(CFLAGSa) -c test_lists.c

DIGRAPHmatrix.o: DIGRAPHmatrix.h DIGRAPHmatrix.c
	gcc $(CFLAGSa) -c DIGRAPHmatrix.c

DIGRAPHlists.o: DIGRAPHlists.h DIGRAPHlists.c
	gcc $(CFLAGSa) -c DIGRAPHlists.c

main.o:	main.c DIGRAPHlists.h
	gcc $(CFLAGSa) -c main.c -lm

clean:
	rm -f *.o
	rm -f test_lists
	rm -f test_matrix
	rm -f main
