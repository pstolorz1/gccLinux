// SO2 IS1 powt._Sys. operacyjne II_L_gr. 2 LAB02
// Paweł Stolorz
// sp39443@zut.edu.pl
// gcc 39443.so2.lab02.main.c -o lab02 -ldl; gcc -shared -fPIC 39443.so2.lab02.lib.c -o lab2lib.so.0.1 -nostartfiles
// ./lab02 -ab

#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <arpa/inet.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <string.h>

char* funkcja(uid_t uid)
{
    int ngroups = 32;
    gid_t groups[50];
    struct passwd *pw = getpwuid(uid);
    struct group *gr;
    getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups);
    char *tmp = malloc(sizeof(char) * 100);
    strcpy(tmp, "");
    for (int j = 0; j < ngroups; j++) 
    {
    	gr = getgrgid(groups[j]);
        strcat(tmp, gr->gr_name);
		strcat(tmp, " ");
    }
    return tmp;
}
