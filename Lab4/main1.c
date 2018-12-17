#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/types.h>

#define FILE "FILE_MEMMORY"

int main()
{
    key_t smkey = ftok("/tmp", 'z');
	int smid = shmget (smkey, 50, IPC_CREAT|0666);
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
		sleep(1);
        time_t tt = time(0);
		sprintf(ad, "%s", ctime(&tt));
	}
	printf ("%d, %d\n", smkey, smid);
	exit (0);
}
