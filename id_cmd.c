#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char **argv)
{
  struct passwd* pw_struct = getpwuid(getuid());
  int groupsSize = getgroups(0, NULL);
  gid_t* groups = (gid_t*)malloc(sizeof(gid_t) * groupsSize);
  if(groups != NULL)
    getgroups(groupsSize, groups);
 
  int uArg = 0, gArg = 0, flag = 0;
  while ((flag = getopt(argc, argv, "ug")) != -1)
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
  
  if(pw_struct != NULL)
  {
    if(uArg == 1)
    {
      printf("%d\n", pw_struct->pw_uid);
    }
    else if(gArg == 1)
    {
      printf("%d\n", pw_struct->pw_gid);
    }
    else
    {
      printf("uid=%d(%s) gid=%d(%s) ", pw_struct->pw_uid, pw_struct->pw_name, pw_struct->pw_gid, pw_struct->pw_name);

      struct group* gr_struct_user = getgrgid(pw_struct->pw_gid);
      if(gr_struct_user != NULL)
        printf("groups=%d(%s)", gr_struct_user->gr_gid, gr_struct_user->gr_name);

      for(int i = 0; i < groupsSize; i++)
      {
        struct group* gr_struct = getgrgid(groups[i]);
        if(gr_struct != NULL)
        {
          if(gr_struct->gr_gid < 1000)
            printf(",%d(%s)", gr_struct->gr_gid, gr_struct->gr_name);
        }
      }
      printf("\n");
    }
  }

  free(groups);

  return 0;
}
