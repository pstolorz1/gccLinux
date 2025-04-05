#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#ifndef Ksiegowosc_h
#define Ksiegowosc_h
class Ksiegowosc
{
private:
	int zarobki;
	int wydatki;
	string kalendarz[12] = {"STYCZEN", "LUTY", "MARZEC", "KWIECIEN", "MAJ", "CZERWIEC", "LIPIEC", "SIERPIEN", "WRZESIEN", "PAZDZIERNIK", "LISTOPAD", "GRUDZIEN"};
public:
	Ksiegowosc(int z = 0, int w =0)  
	{
		zarobki = z; 
		wydatki = w;
	} 

	Ksiegowosc operator+ (Ksiegowosc const &obj) 
	{ 
         Ksiegowosc acc; 
         acc.zarobki = zarobki + obj.zarobki; 
         acc.wydatki = wydatki + obj.wydatki; 
         return acc; 
    }

	void print_dodaj() 
	{ 
		cout << zarobki << "+" << wydatki << endl; 
	} 

	Ksiegowosc operator- (Ksiegowosc const &obj) 
	{ 
         Ksiegowosc acc; 
         acc.zarobki = zarobki - obj.zarobki; 
         acc.wydatki = wydatki - obj.wydatki; 
         return acc; 
    }
	
	void print_odejmij() 
	{ 
		cout << zarobki << "-" << wydatki << endl; 
	} 

	friend ostream& operator<<(ostream& os, const Ksiegowosc& acc)
	{
    	os << "zarobki = " << acc.zarobki << " wydatki = " << acc.wydatki<<endl;
    	return os;
	}

	friend istream& operator>>(istream& is, Ksiegowosc& acc)
	{
    	is >> acc.zarobki >> acc.wydatki;
    	return is;
	}

	void operator= (Ksiegowosc &acc)
	{
		zarobki = acc.zarobki;
		wydatki = acc.wydatki;
	}

	string& operator[] (const int index)
	{
    	return kalendarz[index];
	}

	Ksiegowosc operator() (int a, int b, int c) 
	{
		Ksiegowosc acc;
		acc.wydatki = a + c + 500;
        acc.zarobki = b + c + 200;
        return acc;
    }
};

#endif
