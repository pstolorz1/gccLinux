// SO2 IS1 powt._Sys. operacyjne II_L_gr. 2 LAB01
// Paweł Stolorz
// sp39443@zut.edu.pl
// gcc 39443.so2.lab01.main.c -o lab01
// ./lab01 -ab

#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>

int main(int argc, char **argv)
{
	int opt_a = 0, opt_b = 0, opt;

	struct utmp *utmp_struct;

	int ngroups = 32;
    gid_t *groups;
    struct passwd *pw;
    struct group *gr;
	
	while ((opt = getopt (argc, argv, "ab")) != -1)
	{
		switch (opt) 
		{
			case 'a': 
				opt_a = 1; 
			break;

			case 'b': 
				opt_b = 1; 
			break;
			default: abort();
		}
	}

	setutent();
	while(utmp_struct = getutent())
   	{
		if(utmp_struct->ut_type == 7)
		{
		    printf("%s", utmp_struct->ut_user);

			if(opt_a == 1)
	   			printf(" (%s)", utmp_struct->ut_host);

			if(opt_b == 1)
			{
				groups = malloc(ngroups * sizeof (gid_t));
				pw = getpwnam(utmp_struct->ut_name);
				getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups);
				printf(" [ ");
		    	for(int j = 0; j < ngroups; j++)
				{
					gr = getgrgid(groups[j]);
					printf("%s ", gr->gr_name);
				}
				printf("]");
			}
		}
		printf("\n");
  	}
	printf("\n");
	endutent();
	return 0;
}
