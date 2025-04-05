#include <iostream>
#include <cmath>
#include <cstdio>
#include <math.h>

using namespace std;

int xor2(int a, int b)
{
	return(a^b);
}

int xor3(int a, int b, int c)
{
	return(a^b^c);
}

int absolute(int x)
{
    if(x<0)
        return(-x);
    else
        return(x);
}

void f1(int *tab1, int a, int b, int c, int d)
{
    tab1[0]=a;
    tab1[1]=b;
    tab1[2]=c;
    tab1[3]=d;
}

void f2(int tab1[], int *tab2)
{
	tab2[0]=tab1[0];
	tab2[1]=tab1[1];
	tab2[2]=tab1[2];
	tab2[4]=tab1[3];
	tab2[6]=xor3(tab2[4], tab2[2], tab2[0]);
	tab2[5]=xor3(tab2[4], tab2[1], tab2[0]);
	tab2[3]=xor3(tab2[2], tab2[1], tab2[0]);
}

void f3(int *tab2, int index)
{
	tab2[index]=!tab2[index];
}

int S(int *tab2)
{
    int x1_p=xor3(tab2[4], tab2[2], tab2[0]);
	int x2_p=xor3(tab2[4], tab2[1], tab2[0]);
	int x4_p=xor3(tab2[2], tab2[1], tab2[0]);
	int x1_=xor2(tab2[6], x1_p);
	int x2_=xor2(tab2[5], x2_p);
	int x4_=xor2(tab2[3], x4_p);
    return(x1_*1 + x2_*2 + x4_*4);
}

int main()
{
    int tab1[4], tab2[7];

	f1(tab1, 1, 0, 1, 1);
	printf("POCZATKOWA TABLICA 4 BITOW: ");
	for(int i=0; i<=3; i++)
		printf("%d", tab1[i]);
	printf("\n");

	f2(tab1, tab2);
	printf("ZAMIANA NA TABLICE 7 BITOW: ");
	for(int i=0; i<=6; i++)
		printf("%d", tab2[i]);
	printf("\n");

	printf("NEGACJA BITU ZEBY SPOWODOWAC PRZEKLAMANIE: ");
	f3(tab2, 2);
	for(int i=0; i<=6; i++)
		printf("%d", tab2[i]);
	printf("\n");

	printf("SPRAWDZENIE KTORY BIT JEST PRZEKLAMANY: x");
	printf("%d\n", S(tab2));

	printf("ZAMIANA BITU NA WLASCIWY I WYSWIETLENIE TABLICY: ");
	f3(tab2, absolute((S(tab2))-7));
	for(int i=0; i<=6; i++)
		printf("%d", tab2[i]);

	return 0;
}
