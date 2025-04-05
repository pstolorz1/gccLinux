#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#ifndef Klient_h
#define Klient_h

namespace Dziennik
{
class Klient
{
private:
    string imie;
public:
    Klient(string name)
    {
        imie=name;
    }

    Klient(const Klient &klient)
    {
        imie=klient.imie;
    }

    string get_imie()
    {
        return imie;
    }

	void dodaj_do_dziennika(){cout<<"KLIENT DODANY DO DZIENNIKA"<<endl;};

};
}
#endif
