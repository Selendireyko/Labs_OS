#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define FIFO_FILE "FIFO_NAME"

int main ()
{
	unlink (FIFO_FILE); /// �������� �����
	int fifo = mkfifo (FIFO_FILE, 0666); /// �������� FIFO �����
	if (fifo == -1)
        {
            printf ("Create ERROR\n");
            exit (0);
        }
	pid_t pid; /// ���������� ��� ��������� id ��������
	pid = fork();
	switch (pid)
	{
        case -1:  /// ������ ��������
		printf ("Create ERROR\n");
		exit (0);
		break;
        case 0:  /// ��������� � �������� �������
        {
            int fifo_read = open(FIFO_FILE, O_RDONLY);
            if (fifo_read == -1)
            {
                printf ("FIFO open ERROR\n");
                exit (0);
            }
            int len = 0;
            char *buf = (char*) calloc (50, sizeof (char)); /// ��������� ������ ��� �����
            read (fifo_read, buf, 50);
            close (fifo_read);
            printf ("%d - doch id\n", getpid());
            printf ("%s\n", buf); /// ����� �������
            break;
        }
	default: /// pid ��������� ��������
	{
		int fifo_write = open(FIFO_FILE, O_WRONLY);
		if (fifo_write == -1)
            {
                printf ("FIFO write ERROR\n");
                exit (0);
            }
		time_t t_p = time (0);
		write (fifo_write, ctime(&t_p), 50); /// ������ ������� � ����
		printf ("%d - parent id\n", getpid());
		close (fifo_write);
		break;
	}
	}
	exit (0);
}
