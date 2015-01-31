#include <stdio.h>
#include "linha.h"

#define MAXLINE 2*1024

int main(int ac, char **av) {
	char linha[MAXLINE];

	if (ac != 2)
		fprintf(stderr, "Uso:\n\t%s padrao\n", av[0]);
	else while (pegalinha(linha, MAXLINE))
		if (procura(linha, av[1]) >= 0)
			printf("%s", linha);
	return 0;
}