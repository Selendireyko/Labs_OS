#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>

#define FILE "FILE_MEMMORY"

struct sembuf sm_lock = {0,-1,0}, sm_open = {0,1,0};
int main()
{
    key_t shmkey = ftok("/tmp", 'z');
    int smid = shmget (shmkey, 50, 0666);
    int sm = semget (shmkey, 1, 0666);
	if (sm == -1)
    {
		printf ("Create ERROR\n");
		exit (0);
	}
	if (smid == -1)
    {
        printf ("Memory ERROR\n");
        exit (0);
    }
    char* ad = shmat (smid, NULL, 0);
    if (ad == (char*)-1)
    {
        printf ("Connection ERROR\n");
        exit (0);
    }
    while (1)
    {
        if (semctl(sm, 0, GETVAL) == 1)
        {
            printf("%s", ad);
            semctl(sm, 0, SETVAL, 2);
        }
        // sleep (1);
        // semop (sm , &sm_lock, 1);
		// semop (sm, &sm_open, 1);
    }
    exit (0);
}
