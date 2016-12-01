# DECLARO QUE SOU O UNICO AUTOR E RESPONSAVEL POR ESTE PROGRAMA.
# TODAS AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS
# PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE
# SEDGEWICK OU ROBERTS, FORAM DESENVOLVIDAS POR MIM.  DECLARO
# TAMBEM QUE SOU RESPONSAVEL POR TODAS AS COPIAS DESTE PROGRAMA
# E QUE NAO DISTRIBUI NEM FACILITEI A DISTRIBUICAO DE COPIAS.
# 
# Autor: Gustavo Estrela
# Numero USP: 8536051
# Sigla:      GUSTAVOE
# Data:       2016-08-17
# 
# Este arquivo faz parte da tarefa C
# da disciplina MAC0328.
# 

# Neste arquivo escrevemos um makefile simples para compilação da 
# tarefa C. Este arquivo é baseado em um outro makefile disponivel em:
# http://www.ime.usp.br/~pf/algoritmos/apend/Makefile

# variaveis que serao usadas como opcoes do gcc
CFLAGSa = -Wall -Wno-unused-result -ansi -O0 -pedantic -g
CFLAGSb = -Wall -O2
#    -ansi proibe comentarios com prefixo '//'
#    -g flag de debug

distancia: distancia.o wDIGRAPHlists.o PQ.o
	gcc $(CFLAGSa) distancia.o wDIGRAPHlists.o PQ.o -o distancia

wDIGRAPHlists.o: wDIGRAPHlists.h wDIGRAPHlists.c
	gcc $(CFLAGSa) -c wDIGRAPHlists.c -lm

PQ.o: PQ.h PQ.c
	gcc $(CFLAGSa) -c PQ.c

distancia.o: distancia.c wDIGRAPHlists.h PQ.h
	gcc $(CFLAGSa) -c distancia.c

clean:
	rm -f *.o
	rm -f distancia
