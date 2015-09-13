#include<stdio.h>

int main () 
{
    long l = 0;
    long long ll = 0;

    while (l != l + 1 && l < l + 1)
        l++;

   // while (ll != ll + 1 )
   //     ll + 1;

    printf ("Maior long without gaps: %ld\n", l);
   // printf ("Maior long long without gaps: %lld\n", ll);
    return 0;
}
