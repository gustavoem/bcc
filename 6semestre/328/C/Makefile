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
CFLAGSa = -Wall -Wno-unused-result -ansi -O2 -pedantic -g
CFLAGSb = -Wall -O0
#    -ansi proibe comentarios com prefixo '//'
#    -g flag de debug

traco: traco.o DIGRAPHlists.o
	gcc $(CFLAGSa) traco.o DIGRAPHlists.o -o traco

DIGRAPHlists.o: DIGRAPHlists.h DIGRAPHlists.c
	gcc $(CFLAGSa) -c DIGRAPHlists.c

traco.o: traco.c DIGRAPHlists.h
	gcc $(CFLAGSa) -c traco.c

clean:
	rm -f *.o
	rm -f traco
