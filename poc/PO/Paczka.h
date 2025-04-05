#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#ifndef Paczka_h
#define Paczka_h
class Paczka
{
private:
    int ID;
    float waga;
    friend void wyswietl_paczke_o_indexie(Paczka **paczka, int index);
public:
    int get_ID() const
	{
	    return ID;
	}

	float get_waga() const
	{
	    return waga;
	}

    void set_ID(int x)
    {
        ID = x;
    }
	void set_waga(float x)
	{
	    waga = x;
    }

	Paczka operator+(Paczka)
	{ 
		Paczka temp;
		temp.ID=this->ID + temp.ID;
		temp.waga=this->waga + temp.waga;
		return temp; 
	};
	
	Paczka operator-(Paczka)
	{ 
		Paczka temp;
		temp.ID=this->ID - temp.ID;
		temp.waga=this->waga - temp.waga;
		return temp; 
	};

};
#endif
