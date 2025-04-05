#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char **argv)
{
  struct passwd *pw_struct = getpwuid(getuid());
  int groupsSize = getgroups(0, NULL);
  gid_t *groups = (gid_t*)malloc(sizeof(gid_t) * groupsSize);
  getgroups(groupsSize, groups);
 
  int uArg = 0, gArg = 0, flag;
  while ((flag = getopt (argc, argv, "ug")) != -1)
  {
    switch(flag)
    {
      case 'u':
        uArg = 1;
        break;
      case 'g':
        gArg = 1;
        break;
      default:
        break;
    }
  }
  
  if(uArg == 1)
  {
    if(pw_struct != NULL)
    {
      printf("ARG -u\n");
      printf("%d\n", pw_struct->pw_uid);
    }
  }
  else if(gArg == 1)
  {
    if(pw_struct != NULL)
    {
      printf("ARG -g\n");
      printf("%d\n", pw_struct->pw_gid);
    }
  }
  else
  {
    if(pw_struct != NULL)
    {
      printf("NO ARG\n");
      printf("uid=%d(%s) gid=%d(%s) ", pw_struct->pw_uid, pw_struct->pw_name, pw_struct->pw_gid, pw_struct->pw_name);
      
      printf("groups=");
      for(int i = 0; i < groupsSize; i++)
      {
        struct group *gr_struct = getgrgid(groups[i]);
        if (gr_struct != NULL)
          printf("%d(%s) ", gr_struct->gr_gid, gr_struct->gr_name);
      }
      printf("\n");
    }
  }
    
  free(groups);

  return 0;
}
