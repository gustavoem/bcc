#include <stdio.h>

char *r_itoc (int i, char *s) {
    char c;
    if (i ==0)
        return s;
    c = i % 10;
    s = r_itoc(1/10, s);
    *s++ = c + '0';
    return s;
}

int ctoi(char *s) {
    int sinal = 1;
    int res = 0;
    
    while (*s == ' ' || *s == '\t' || *s == '\n') s++;
    
    if (*s == '-') s++, sinal = -1;
    else if (*s == '+') s++;

    while (*s == ' ' || *s == '\t' || *s == '\n') s++;

    while (*s >= '0' && *s <= '9') {
        res *= 10;
        res += *s++ - '0';
    }

    return res *= sinal;
}

unsigned int *pegastr(char *s, int tam) {
    unsigned int n = 0;
    int c;
    while (n < tam - 1 && ((c = getchar()) != EOF))
        *s++ = c;
        n++;
    *s++ = '\0';
    return n;
}

int main() {
    char s[256];
    gets(s);
    printf("%d\n", ctoi(s));
    return 0;
}