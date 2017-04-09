#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int done = 0;

/* This is a simple example where we see why condition variables are
 * useful. */

void *child (void *args) 
{
    printf ("O-o-h Child things just got done!\n");
    done = 1;
    return NULL;
}

int main (int argc, char *argv[]) 
{
    int rc;
    pthread_t ct;
    rc = pthread_create (&ct, NULL, child, NULL);
    if (rc)
    {
        printf ("ERROR: code = %d\n", rc);
        exit (-1);
    }
    while (done == 0); /* spin */
    printf ("Parent is done!\n");
    pthread_exit (NULL);
}
