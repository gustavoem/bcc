#include <stdio.h>
#include "linha.h"

int pegalinha(char *s, int tam) {
	int c = 0, i = 0;

	while (--tam > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if (c == '\n') s[i++] = c;

	s[i] = '\0';
	return i;
}

int procura(char *s, char *t) {
	char *a, /* a avança em t (alvo)*/
		 *b; /* b avança em s */
	int i;	 /*indice do caractere testado*/

	for (b = s; *b; b++) {
		for (a = t, i = 0; *a && b[i] == *a; i++, a++);
		if (! *a) return (b-s);
	}
	return -1;
}