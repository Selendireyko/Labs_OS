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
	unlink (FIFO_FILE); /// удаление файла
	int fifo = mkfifo (FIFO_FILE, 0666); /// создание FIFO файла
	if (fifo == -1)
        {
            printf ("Create ERROR\n");
            exit (0);
        }
	pid_t pid; /// переменная для храниения id процесса
	pid = fork();
	switch (pid)
	{
        case -1:  /// ошибка создания
		printf ("Create ERROR\n");
		exit (0);
		break;
        case 0:  /// попадание в дочерний процесс
        {
            int fifo_read = open(FIFO_FILE, O_RDONLY);
            if (fifo_read == -1)
            {
                printf ("FIFO open ERROR\n");
                exit (0);
            }
            int len = 0;
            char *buf = (char*) calloc (50, sizeof (char)); /// выделение памяти под сроку
            read (fifo_read, buf, 50);
            close (fifo_read);
            printf ("%d - doch id\n", getpid());
            printf ("%s\n", buf); /// вывод времени
            break;
        }
	default: /// pid дочернего процесса
	{
		int fifo_write = open(FIFO_FILE, O_WRONLY);
		if (fifo_write == -1)
            {
                printf ("FIFO write ERROR\n");
                exit (0);
            }
		time_t t_p = time (0);
		write (fifo_write, ctime(&t_p), 50); /// запись времени в ФИФО
		printf ("%d - parent id\n", getpid());
		close (fifo_write);
		break;
	}
	}
	exit (0);
}
