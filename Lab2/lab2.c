#include <stdlib.h>
#include <dirent.h> 
#include <unistd.h>
#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(void)
{
  DIR *d;
  int n = 0;
  struct dirent *dir = (struct dirent*) calloc (sizeof (struct dirent)+1, 1);
  struct dirent **namelist;
  struct stat *buff;
  time_t t;
  buff = (struct stat*) calloc (sizeof(struct stat), 1);
  n = scandir (".", &namelist, NULL, alphasort);
  int i=0;
  while (i<n)
    {
      dir = namelist[i];
      stat (dir->d_name, buff);
      
      printf ((buff->st_mode & S_IFDIR)?"d":"-");
      printf ((buff->st_mode & S_IRUSR)?"r":"-");
      printf ((buff->st_mode & S_IWUSR)?"w":"-");
      printf ((buff->st_mode & S_IXUSR)?"x":"-");
      printf ((buff->st_mode & S_IRGRP)?"r":"-");
      printf ((buff->st_mode & S_IWGRP)?"w":"-");
      printf ((buff->st_mode & S_IXGRP)?"x":"-");
      printf ((buff->st_mode & S_IROTH)?"r":"-");
      printf ((buff->st_mode & S_IWOTH)?"w":"-");
      printf ((buff->st_mode & S_IXOTH)?"x":"-");
      

      struct passwd *pw = getpwuid(buff -> st_uid);
      struct group  *gr = getgrgid(buff -> st_gid);
      printf(" %d", buff -> st_nlink);
      printf(" %s", pw -> pw_name);
      printf(" %s", gr -> gr_name);
      printf (" %lld", buff->st_size);

      char mtime[80];
      t = buff->st_mtime;
      struct tm lt;
      localtime_r(&t, &lt);
      strftime(mtime, sizeof mtime, "%d %b %Y %T", &lt);
      printf (" %s", mtime);
      printf (" %s\n", dir->d_name);
      free (namelist[n]);
      i++;
    }
  return(0);
}
