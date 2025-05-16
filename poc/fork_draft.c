// gcc fork_draft.c -lm
// ./a.out abcde

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <sys/wait.h>
#include <dlfcn.h>
#include <string.h>
#include <math.h>
#include <limits.h>

void argv_cut(char *string, char *string2, int dlugosc)
{
	int i;
	int pot=0;
	int dlugosc_skrocona;
	
	do
	{
		pot++;
  		dlugosc_skrocona = pow(2, pot);
	}
	while((dlugosc_skrocona*2)<=dlugosc);
	
	for(i=0; i<dlugosc_skrocona; i++)
		string2[i]=string[i];
}

pid_t child1;
pid_t child2;
char poczatek[16];
char koniec[16];
char skrocone[32];
char temp[PATH_MAX];

int main(int argc, char **argv)
{
	if(argc > 1)
	{
		argv_cut(argv[1], skrocone, strlen(argv[1]));
		int dlugosc1 = strlen(skrocone);
		int dlugosc2 = dlugosc1/2;

		if(dlugosc1 >= 1)	
		{	
			strncpy(poczatek, skrocone, dlugosc2);
			strncpy(koniec, skrocone+dlugosc2, dlugosc2);
			printf("%d ", getpid());
			int j;
			if(argv[2]==NULL)
			{
				printf(" ");
				for(j=0; j<dlugosc1; j++)
					printf("%c", skrocone[j]);
			}
			else
			{
				printf("%s ", argv[2]);
				for(j=0; j<dlugosc1; j++)
					printf("%c", skrocone[j]);    			
			}
			printf("\n");
		}
		else
		{
			exit(0);
		}
	}
	else
	{
		printf("BRAK ARGUMENTOW\n");
		exit(0);
	}

	if (argv[2] == NULL)
       		argv[2] = "";	
	strcat(temp, argv[2]);
   	strcat(temp, " ");
	strcat(temp, skrocone);

	if((child1 = fork()) == 0)
	{
		argv[1] = poczatek;
		argv[2] = temp;
		execv("a.out", argv);	
	}

	if((child2 = fork()) == 0)
	{
		argv[1] = koniec;	
		argv[2] = temp;
		execv("a.out", argv);	
	}
	
	while(wait(NULL)>0) 
	while(wait(NULL)>0)
	return 0;
}

