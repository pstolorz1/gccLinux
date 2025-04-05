#include <iostream>
#include <conio.h>

using namespace std;

class punkt
{
protected:
    int a;
    int b;
public:
    void przypisz(int x, int y)
    {
        a=x;
        b=y;
    }
    void przypisz(int x)
    {
        a=x;
    }
};

class kwadrat : public punkt
{
public:
    int pole()
    {
        return(a*b);
    }

    int obwod()
    {
        return(4*a);
    }
    int nazwa()
    {
        cout<<"kwadrat"<<endl;
        return(0);
    }
};

class trojkat : public punkt
{
public:
    int pole()
    {
        return(a*b/2);
    }
    int obwod()
    {
        return(3*a); //zalozmy, ze jest rownoboczny
    }
     int nazwa()
    {
        cout<<"trojkat"<<endl;
        return(0);
    }
};

class kolo : public punkt
{
public:
    int pole()
    {
        return(a*a);
    }
    int obwod()
    {
        return(2*a);
    }
     int nazwa()
    {
        cout<<"kolo"<<endl;
        return(0);
    }
};


int main()
{
    kwadrat pole_kw;
    kwadrat obwod_kw;
    kwadrat nazwa_kw;

    trojkat pole_tr;
    trojkat obwod_tr;
    trojkat nazwa_tr;

    kolo pole_kola;
    kolo obwod_kola;
    kolo nazwa_kola;

    pole_kw.przypisz(5,6);
    obwod_kw.przypisz(4);

    pole_tr.przypisz(4, 4);
    obwod_tr.przypisz(10);

    pole_kola.przypisz(6);
    obwod_kola.przypisz(9);

    cout<<pole_kw.pole()<<endl;
    cout<<obwod_kw.obwod()<<endl;
    cout<<nazwa_kw.nazwa()<<endl;

    cout<<pole_tr.pole()<<endl;
    cout<<obwod_tr.obwod()<<endl;
    cout<<nazwa_tr.nazwa()<<endl;

    cout<<pole_kola.pole()<<"pi"<<endl;
    cout<<obwod_kola.obwod()<<"pi"<<endl;
    cout<<nazwa_kola.nazwa()<<endl;

    getch();
    return 0;
}
