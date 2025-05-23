// gcc fork_draft.c
// ./a.out abcdef
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

static pid_t child1;
static pid_t child2;
static char firstHalf[16];
static char secondHalf[16];
static char argvShortened[32];

void argvSplit(const char* stringOriginal, char* stringShortened, int length)
{
	unsigned char exponent = 0;
	unsigned char lengthShortened = 0;

	while(lengthShortened * 2 <= length)
		lengthShortened = 1 << (exponent++);
	
	strncpy(stringShortened, stringOriginal, lengthShortened);
}

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		argvSplit(argv[1], argvShortened, strlen(argv[1]));

		if(strlen(argvShortened) >= 1)
		{
			strncpy(firstHalf, argvShortened, strlen(argvShortened)/2);
			strncpy(secondHalf, argvShortened + strlen(argvShortened)/2, strlen(argvShortened)/2);

			if(argv[2] == NULL)
			{
				printf("%d %s\n", getpid(), argvShortened);
			}
			else
			{
				printf("%d %s %s\n", getpid(), argv[2], argvShortened);	
			}
		}
		else
		{
			exit(0);
		}
	}
	else
	{
		printf("MISSING ARGUMENT!\n");
		exit(0);
	}

	if((child1 = fork()) == 0)
	{
		argv[1] = firstHalf;
		if(argv[2] != NULL)
		{
			strcat(argv[2], " ");
			strcat(argv[2], argvShortened);
		}
		// Currently executed program
		execv("/proc/self/exe", argv);
	}

	if((child2 = fork()) == 0)
	{
		argv[1] = secondHalf;
		if(argv[2] != NULL)
		{
			strcat(argv[2], " ");
			strcat(argv[2], argvShortened);
		}
		// Currently executed program
		execv("/proc/self/exe", argv);
	}

	while(wait(NULL)>0)
	while(wait(NULL)>0)
	return 0;
}

