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

pthread_mutex_t mut;
void* thread_func ()
{
    key_t shmkey = ftok("/tmp", 'z');
    int smid = shmget (shmkey, 50, 0666);
	if (smid == -1)
    {
    	printf ("Create ERROR\n"); ///ошибка создания разделяемой памяти
        exit (0);
    }
    char* ad = shmat (smid, NULL, 0);
	if (ad == (char*)-1)
    {
		printf ("Connection ERROR\n"); /// ошибка подключения разделяемой памяти
		exit (0);
	}
    time_t timer;
	while (1)
	{
        timer = time(0);
        pthread_mutex_lock(&mut); ///блокировка потоков
        sprintf(ad, "%s", ctime(&timer));
        pthread_mutex_unlock(&mut);
		sleep (1);
	}
	exit (0);
}

int main()
{
	pthread_t pot; /// id потока
	pthread_mutex_init (&mut, NULL);
	int stat = pthread_create (&pot, NULL, thread_func, NULL);
	if (stat != 0)
    {
		printf ("%d Create ERROR\n", stat);
		exit (0);
	}
	key_t shmkey = ftok("/tmp", 'z');
	int smid = shmget (shmkey, 50, IPC_CREAT|0666);
	if (smid == -1)
	{
		printf ("Create ERROR\n");
		exit (0);
	}
    char* ad = shmat (smid, NULL, 0);
	if (ad == (char*)-1)
	{
		printf ("Memorry ERROR\n");
		exit (0);
	}
	while (1)
	{
        pthread_mutex_lock (&mut);
		printf ("%s\n", ad);
		pthread_mutex_unlock(&mut);
		sleep(1);
	}
	pthread_mutex_destroy(&mut);
	exit (0);
}

