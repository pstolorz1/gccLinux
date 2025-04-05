// wyjatki.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>

int dodaj(int x, int y)
{
	if (x == 5 || y == 10)
	{
		throw 1;
	}
	return(x + y);
}

int main()
{
	try 
	{
		dodaj(5, 10);
	}

	catch(int p)
	{
		if (p == 1)
			printf("test blad");
	}
	//printf("%d", dodaj(5, 10));
	printf("%d", dodaj(1, 4));
	_getch();
    return 0;
	//zaprzyjaünienie!!!!
}

