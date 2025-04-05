#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#ifndef Pracownik_h
#define Pracownik_h

namespace Dziennik
{
class Pracownik
{
private:
    string nazwisko;
    Pracownik *nastepny;
    static Pracownik *lista;
public:
    Pracownik(string t):nazwisko(t)
    {
        nastepny=lista;
        lista=this;
    }
    void pokaz() const
    {
        cout<<nazwisko<<endl;
    }
    static void pokaz_liste()
	{
    	for(Pracownik *p=lista; p; p=p->nastepny)
    	    p->pokaz();
	}

	void dodaj_do_dziennika(){cout<<"PRACOWNIK DODANY DO DZIENNIKA"<<endl;};
};

Pracownik *Pracownik::lista=NULL;

}
#endif
