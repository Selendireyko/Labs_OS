#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/shm.h>

#define FILE "FILE_MEMMORY"

pthread_rwlock_t lk;

void* thread_func ()
{
    key_t shmkey = ftok("/tmp", 'z');
    int smid = shmget (shmkey, 50, 0666);
    if (smid == -1)
    {
        printf ("MEMORY ERROR\n");
        exit (0);
    }
    char* ad = shmat (smid, NULL, 0);
    if (ad == (char*)-1)
    {
        printf ("Connecntion ERROR\n");
        exit (0);
    }
    time_t timer;
    while (1)
    {
        timer = time(0);
        pthread_rwlock_wrlock(&lk);
        sprintf(ad, "%s", ctime(&timer));
        pthread_rwlock_unlock(&lk);
        sleep (2);
    }
    exit (0);
}

int main()
{
    pthread_t pth;
    pthread_rwlock_init (&lk, NULL);
    int st = pthread_create (&pth, NULL, thread_func, NULL);
    if (st != 0)
    {
        printf ("%d Creat potok ERROR\n", st);
        exit (0);
    }
    key_t shmkey = ftok("/tmp", 'z');
    int smid = shmget (shmkey, 50, IPC_CREAT|0666);
    if (smid == -1)
    {
        printf ("MEMORY ERROR\n");
        exit (0);
    }
    char* ad = shmat (smid, NULL, 0);
    if (ad == (char*)-1)
    {
        printf ("Connecntion ERROR\n");
        exit (0);
    }
    while (1)
    {
        sleep(1);
        pthread_rwlock_wrlock(&lk);
        printf ("%s\n", ad);
        pthread_rwlock_unlock(&lk);
    }
    pthread_rwlock_destroy(&lk);
    exit (0);
}

