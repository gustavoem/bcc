#include <stdio.h>
#include <sys/time.h> 

int main()
{
    unsigned int uint;
    double dbl;
    long lon;
    long long lonlon;
    char ch;
    float fl;
    struct timeval tmv;


    FILE *my_file_pointer;
    if ((my_file_pointer = fopen ("lab1_prob2_out.txt", "w")) == NULL)
    {
        printf ("Error opening the file, so exiting\n");
        return 1;
    }

    fprintf (my_file_pointer, "The sizes of different data type for this machine and compiler are -\n");

    lon = 9.223372e+18 + 101312313;
    printf ("Valor de lon: %30lu", lon);

    printf ("The sizes of different data type for this machine and compiler are -\n");
    printf ("unsigned int data type is %lu bytes or %lu bits long\n", sizeof (unsigned int), sizeof (unsigned int) * 8);
    printf ("double data type is %lu bytes or %lu bits long\n", sizeof (double), sizeof (double) * 8);
    printf ("long data type is %lu bytes or %lu bits long\n", sizeof (long), sizeof (long) * 8);
    printf ("long long data type is %lu bytes or %lu bits long\n", sizeof (long long), sizeof (long long) * 8);
    printf ("char data type is %lu bytes or %lu bits long\n", sizeof (char), sizeof (char) * 8);
    printf ("float data type is %lu bytes or %lu bits long\n", sizeof (float), sizeof (float) * 8);
    printf ("struct timeval data type is %lu bytes or %lu bits long\n", sizeof (tmv), sizeof (tmv) * 8);
    fclose (my_file_pointer);

    return 0;
}
