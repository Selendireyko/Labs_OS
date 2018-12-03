#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main()
{
  long int t;
  pid_t id;
  int m=0;
  switch (id=fork())
    {
    case -1:
      t = time (NULL);
      printf ("Error born proc %s\n", ctime(&t));
      break;
    case 0:
      sleep(1);
      t = time (NULL);
      printf ("Child id - %x, Parent id - %x,Time - %s\n", getpid(), getppid(), ctime (&t));
      break;
    default:
      //sleep (5);
      t = time (NULL);
      printf ("Parent id - %x,Time - %s\n", getppid(), ctime (&t));
      break;
    }
  fflush(stdout);
  return 0;
}
