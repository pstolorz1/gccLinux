#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#ifndef Adress_h
#define Adress_h
class Adress
{
private:
    mutable string adres;
public:
    void set_adress(string adress = "Jasna, Warszawa") const
    {
        adres = adress;
    }
    string get_adress() const
    {
        return adres;
    }
};
#endif
