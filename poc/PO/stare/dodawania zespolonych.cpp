#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

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
		cout << *a << " + " << *b << "i" << endl;
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
	float a = 10.0, b = 20.0, c = 200.0;
	Zes z(a, b);
	z.Wypisz();
	Zes z1(a, c);
	z.Dodaj(&z1);
	z.Wypisz();

	Zes *temp =  z.Nowa(&z1);
	temp->Wypisz();
	delete temp;

	Zes *temp1 = z.Nowa2(&z1);
	temp1->Wypisz();
	delete temp1;

	getchar();
    return 0;
}
