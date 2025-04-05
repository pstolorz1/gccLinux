#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#ifndef Pojazd_h
#define Pojazd_h

class Pojazd
{
public:
	virtual void dostarcz_paczke()=0;
};

class Samochod:public Pojazd
{
private:
	string miasto;
public:
	Samochod(string m):miasto(m) {}
	virtual void dostarcz_paczke()
	{
		cout<<"PACZKA ZOSTALA DOSTARCZONA SAMOCHODEM, CEL: "<<miasto<<endl;
	}
};

class Van:public Pojazd
{
private:
	string miasto;
	string wojewodztwo;
public:
	Van(string m, string w):miasto(m), wojewodztwo(w){}
	virtual void dostarcz_paczke()
	{
		cout<<"PACZKA ZOSTALA DOSTARCZONA VANEM, CEL: "<<miasto<<", "<<wojewodztwo <<endl;
	}
};

class Samolot:public Pojazd
{
private:
	string miasto;
	string panstwo;
	string kontynent;
public:
	Samolot(string m, string p, string k):miasto(m), panstwo(p), kontynent(k){}
	virtual void dostarcz_paczke()
	{
		cout<<"PACZKA ZOSTALA DOSTARCZONA SAMOLOTEM, CEL: "<<miasto<<", "<<panstwo<<", "<<kontynent<<endl;
	}
};

#endif
