#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

int count = 0;
pthread_mutex_t count_mutex;
pthread_cond_t count_cv;

/* This is a simple example where we use condition variables to 
 * implement a join-like execution. */

void *child (void *args) 
{
    int tid;
    tid = (int) ((long) args);
   
    pthread_mutex_lock (&count_mutex);
    count++;
    /* In this example we might not need this lock
     * in the if clause...*/
    if (count == NUM_THREADS)
        pthread_cond_signal (&count_cv);
    pthread_mutex_unlock (&count_mutex);
    
    printf ("Thread %d just got it done\n", tid);
    pthread_exit (NULL);
}

int main (int argc, char *argv[]) 
{
    int rc, i;
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init (&count_mutex, NULL);
    pthread_cond_init (&count_cv, NULL);
    for (i = 0; i < NUM_THREADS; i++)
    {
        long tid = (long) i;
        rc = pthread_create (&threads[i], NULL, child, (void *) tid);
        if (rc)
        {
            printf ("ERROR: code = %d\n", rc);
            exit (-1);
        }
    }
    pthread_mutex_lock (&count_mutex);
    while (count < NUM_THREADS)
        pthread_cond_wait (&count_cv, &count_mutex);
    /* Why do we have to pass the mutex as an argument? I believe it's
     * because this last line should yield this thread and unlock the
     * mutex. Also, when this thread gets to run again, it should lock
     * the mutex again. */
    pthread_mutex_unlock (&count_mutex);
    printf ("Parent is done!\n");

    pthread_mutex_destroy (&count_mutex);
    pthread_cond_destroy (&count_cv);
    pthread_exit (NULL);
}
