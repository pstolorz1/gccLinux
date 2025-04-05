// przyjazn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class A
{
private:
	int x;
	friend class B;
	friend void funkcja(A&obiekt);
public:
	void wypisz()
	{
		cout << x << endl;
	}
};

class B
{
public:
	void test(A&obiekt)
	{
		obiekt.x = 10;
	}
};

void funkcja(A&obiekt)
{
	obiekt.x = 10;
}

int main()
{
	A liczba;
	B liczba2;
	liczba2.test(liczba);
	funkcja(liczba);
	
    return 0;
}

