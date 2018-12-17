#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main ()
{
	int p[2]; /// ������ ������ �����
	if (-1 == pipe(p))
	{
		printf ("ERROR\n");
		exit (0);
	}
	pid_t pid;
	pid = fork();
	switch (pid)
	{
        case -1:  /// ������
		printf ("Create ERROR\n");
		exit (0);
		break;
        case 0: /// �������� �������
        {
            sleep (1);
            time_t buf;
            close (p[1]); /// 1-������, 0-�������
            read(p[0], &buf, sizeof (time_t));
            close (p[0]);
            printf ("%s\n", ctime (&buf));
            break;
        }
	default: /// ������������ �������
        {
            time_t t = time (0);
            close (p[0]);
            write (p[1], &t, sizeof (time_t));
            close (p[1]);
            break;
        }
	}
	exit (0);
}
