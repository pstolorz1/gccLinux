// labki 9.11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>

class Zes
{
public:
	float *a;
	float *b;

	Zes(float c, float d)
	{
		a = new float;
		b = new float;
		*a = c;
		*b = d;
	}

	~Zes()
	{
		delete a;
		delete b;
	}

	void Wypisz()
	{
		std::cout << *a << " + " << *b << "i" << std::endl;
	}

	void Dodaj(Zes *klasa)
	{
		*a = *a + *klasa->a;
		*b = *b + *klasa->b;
	}

	Zes * Nowa(Zes *nowa)
	{
		float _a = *a + *(nowa->a);
		float _b = *b + *(nowa->b);
		return new Zes(_a, _b);
	}

	void Odejmij(Zes *klasa)
	{
		*a = *a - *klasa->a;
		*b = *b - *klasa->b;
	}

	Zes * Nowa2(Zes *nowa)
	{
		float _a = *a - *(nowa->a);
		float _b = *b - *(nowa->b);
		return new Zes(_a, _b);
	}
};

int main()
{
    return 0;
}

