// SO2 IS1 powt._Sys. operacyjne II_L_gr. 2 LAB02
// Paweł Stolorz
// sp39443@zut.edu.pl
// gcc 39443.so2.lab02.main.c -o lab02 -ldl; gcc -shared -fPIC 39443.so2.lab02.lib.c -o lab2lib.so.0.1 -nostartfiles
// ./lab02 -ab

#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <string.h>
#include <dlfcn.h>

char* (*funkcja)(uid_t uid);

int main(int argc, char **argv)
{
	int opt_a = 0, opt_b = 0, opt;
	struct utmp *utmp_struct;
    struct passwd *pw;
	
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
		        void *handle = dlopen("./lab2lib.so.0.1", RTLD_LAZY);

		        if (!handle)
		            dlerror();
				else
				{
					char *tmp = malloc(sizeof(char) * 100);
					funkcja = dlsym(handle,"funkcja");  
					pw = getpwnam(utmp_struct->ut_user);					
		            uid_t tmp2 = pw->pw_uid;					
		            tmp = funkcja(tmp2);			
		            printf(" [ %s]\n", tmp);				
		            dlclose(handle);
				}
			}
		}
		printf("\n");
  	}
	printf("\n");
	endutent();
	return 0;
}

