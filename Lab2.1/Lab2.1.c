#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <string.h>

#define FILE_1 "FILE_1_1"
#define FILE_2 "FILE_2_2"
#define FILE_SIZE 100000000
#define FILE_SIZE_BUF 1000

char data [] = "dlcnjfoslc";

bool create ()
{
    int fd = open(FILE_1, O_RDWR|O_TRUNC|O_CREAT, S_IWRITE|S_IREAD);
    if (fd < 0)
    {
        return false;
    }
    close (fd);
    return true;
}

bool writing ()
{
    char * buf = (char*)calloc(FILE_SIZE_BUF, sizeof(char));
    for (int i = 0; i < FILE_SIZE_BUF; i += 10)
    strcat (buf, data);
    int fd = open(FILE_1, O_RDWR|O_TRUNC|O_CREAT, S_IWRITE|S_IREAD);
    if (fd < 0)
    {
        return false;
    }
    else
    {
        for (int i=0; i< FILE_SIZE/FILE_SIZE_BUF; i++)
        {
            write (fd, buf, FILE_SIZE_BUF);
        }
        printf ("CREATING FILE.......\n");
    }
    close (fd);
    return true;
}

bool copying ()
{
    int fd_r = open (FILE_1, O_RDONLY);
    if (fd_r < 0)
    {
        printf ("FILE_1 OPEN ERROR\n");
        return false;
    }
    int fd_w = open (FILE_2, O_CREAT|O_TRUNC|O_WRONLY);
    if (fd_w < 0)
    {
        printf ("FILE_2 OPEN ERROR\n");
        return false;
    }
    char *buf = (char*)calloc(FILE_SIZE_BUF, sizeof(char));
    printf ("\nCOPYING FILE.......\n");
    while (read(fd_r, buf, FILE_SIZE_BUF))
    {
        write (fd_w, buf, FILE_SIZE_BUF);
    }
    printf ("\nCOPYING FILE COMPLITE\n");
    return true;
}

int main ()
{
    if (!create())
    {
        perror ("");
        printf ("CREATE ERROR\n");
        exit (0);
    }
    pid_t pid = fork();
     if (pid == -1)
    {
        printf ("FORK ERROR\n");
        exit (0);
    }
    if (pid == 0)
    {
        sleep (1);
        if (!copying ())
        {
            printf ("COPYING ERROR\n");
            exit (0);
        }
    }
    else
    {
        if (!writing ())
        {
            printf ("WRITING ERROR\n");
            exit (0);
        }
        printf ("\nFILE CREATE COMPLITE\n");
        int stat;
        wait (&stat);
    }
    exit (0);
}

