# variaveis que serao usadas como opcoes do gcc
CFLAGSa = -Wall -Wno-unused-result -ansi -O2 -pedantic -g
CFLAGSb = -Wall -O0
#    -ansi proibe comentarios com prefixo '//'
#    -g prepara o terreno para que o gdb possa caçar bugs

LIBRARIES = -lm
#    necessario no caso de usar math.h

# para produzir o arquivo executavel xxx, 
#    basta dizer "make xxx"

lists: main.o DIGRAPHlists.o
	gcc $(CFLAGSa) main.o DIGRAPHlists.o -o main

matrix: main.o DIGRAPHmatrix.o
	gcc $(CFLAGSa) main.o DIGRAPHmatrix.o -o main

main.o : main.c DIGRAPHmatrix.h DIGRAPHlists.h
	gcc $(CFLAGSa) -c main.c


DIGRAPHmatrix.o : DIGRAPHmatrix.h DIGRAPHmatrix.c
	gcc $(CFLAGSa) -c DIGRAPHmatrix.c

DIGRAPHlists.o : DIGRAPHlists.h DIGRAPHlists.c
	gcc $(CFLAGSa) -c DIGRAPHlists.c

clean:
	rm *.o
