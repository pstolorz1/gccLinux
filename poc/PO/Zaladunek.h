#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
using namespace std;
#ifndef Zaladunek_h
#define Zaladunek_h
class Zaladunek
{
private:
	class Logistics
	{
    private:
        const Adress adr;
    public:
        void dostarcz_paczke()
        {
			adr.set_adress("Jasna, Szczecin");
            cout<<"PACZKA ZOSTALA DOSTARCZONA NA ADRES: "<<adr.get_adress()<<endl;
        }
	};

	Logistics logistics;
	int size;
	int *tab;
	Paczka **paczka;
    void dodaj_paczke();
    void usun_paczke();
    void dodaj_wartosci();
    void wyswietl_wartosci();

public:
	Zaladunek(int x):size(x)
	{

	};

	Zaladunek& operator=(const Zaladunek &zprawejStrony)
	{
		if(&zprawejStrony!=this)
		{
			delete [] tab;
			size = zprawejStrony.size;
			tab = new int[size];
			assert(tab!=0);
			for(int i=0; i<size; i++)
				tab[i]=zprawejStrony.tab[i];
		}
	return *this;
	}

	Zaladunek():Zaladunek(10)
	{
        dodaj_paczke();
        dodaj_wartosci();
        wyswietl_wartosci();
		logistics.dostarcz_paczke();
	}

	~Zaladunek()
	{
      	usun_paczke();
	}
};
#endif
