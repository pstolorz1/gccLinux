#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Paczka.h"
#include "Adress.h"
#include "Zaladunek.h"
#include "Klient.h"
#include "Pracownik.h"
#include "Ksiegowosc.h"
#include "Pojazd.h"

using namespace std;

void wyswietl_paczke_o_indexie(Paczka **paczka, int index)
{
    cout<<"ID PACZKI:"<<paczka[index]->get_ID();
    cout<<" || ";
    cout<<"WAGA PACZKI:"<<paczka[index]->get_waga()<<endl;
}

float float_rand()
{
    float scale = rand() / (float) RAND_MAX;
    return(0.1 + scale * (2.0 - 0.1));
}


void Zaladunek::dodaj_paczke()
{
	paczka = new Paczka*[size];
    for(int i=0; i<size; i++)
	    paczka[i] = new Paczka[size];
}

void Zaladunek::dodaj_wartosci()
{
    for(int i=0; i<size; i++)
    {
        paczka[i]->set_ID(i);
        paczka[i]->set_waga(float_rand());
    }
}

void Zaladunek::wyswietl_wartosci()
{
    for(int i=0; i<size; i++)
    {
        cout<<"ID PACZKI:"<<paczka[i]->get_ID();
        cout<<" || ";
        cout<<"WAGA PACZKI:"<<paczka[i]->get_waga()<<endl;
    }
}

void Zaladunek::usun_paczke()
{
	for(int i=0; i<size; i++)
		delete[] paczka[size];
 	delete[] paczka;
}

void create(Paczka* &paczka, int size)
{
    paczka=new Paczka[size];
}

void create(Paczka** &paczka, int size)
{
    paczka = new Paczka*[size];
    for(int i=0; i<size; i++)
        paczka[i] = new Paczka[size];
}

void initialize(Paczka* const paczka, int const size)
{
    for(int i=0; i<size; i++)
    {
        paczka[i].set_ID(i);
        paczka[i].set_waga(float_rand());
    }
}

void initialize(Paczka* const* paczka, int const size)
{
    for(int i=0; i<size; i++)
    {
        paczka[i]->set_ID(i);
        paczka[i]->set_waga(float_rand());
    }
}

void display(Paczka* const paczka, int const size)
{
    for(int i=0; i<size; i++)
    {
        cout<<"ID PACZKI:"<<paczka[i].get_ID();
        cout<<" || ";
        cout<<"WAGA PACZKI:"<<paczka[i].get_waga()<<endl;
    }
}

void display(Paczka* const* paczka, int const size)
{
    for(int i=0; i<size; i++)
    {
        cout<<"ID PACZKI:"<<paczka[i]->get_ID();
        cout<<" || ";
        cout<<"WAGA PACZKI:"<<paczka[i]->get_waga()<<endl;
    }
}

void usun(Paczka* &paczka, int size)
{
    delete[] paczka;
}

void usun(Paczka** &paczka, int size)
{
    for(int i=0; i<size; i++)
        delete[] paczka[size];
    delete[] paczka;
}

void dodaj_nowy_element(Paczka* &paczka, int &size, int index, int ID)
{
    Paczka *tab_temp;

    create(tab_temp, (size+1));

    for(int i=0; i<(index-1); i++)
    {
        tab_temp[i].set_ID(paczka[i].get_ID());
        tab_temp[i].set_waga(paczka[i].get_waga());
    }

    tab_temp[index-1].set_ID(ID);
    tab_temp[index-1].set_waga(float_rand());

    for(int i=index; i<(size+1); i++)
    {
        tab_temp[i].set_ID(paczka[i-1].get_ID());
        tab_temp[i].set_waga(paczka[i-1].get_waga());
    }

    for(int i=0; i<size; i++)
        paczka[i] = tab_temp[i];

    paczka=tab_temp;
}

void dodaj_nowy_element(Paczka** &paczka, int size, int index, int ID)
{
    Paczka **tab_temp;

    create(tab_temp, (size+1));

    for(int i=0; i<(index-1); i++)
    {
        tab_temp[i]->set_ID(paczka[i]->get_ID());
        tab_temp[i]->set_waga(paczka[i]->get_waga());
    }

    tab_temp[index-1]->set_ID(ID);
    tab_temp[index-1]->set_waga(float_rand());

    for(int i=index; i<(size+1); i++)
    {
        tab_temp[i]->set_ID(paczka[i-1]->get_ID());
        tab_temp[i]->set_waga(paczka[i-1]->get_waga());
    }

    for(int i=0; i<size; i++)
        (*paczka)[i] = (*tab_temp)[i];

    paczka=tab_temp;
}

void usun_element(Paczka* &paczka, int size, int index)
{
    Paczka *tab_temp;

    create(tab_temp, (size-1));

    for(int i=0; i<(index-1); i++)
    {
        tab_temp[i].set_ID(paczka[i].get_ID());
        tab_temp[i].set_waga(paczka[i].get_waga());
    }

    for(int i=(index-1); i<(size-1); i++)
    {
        tab_temp[i].set_ID(paczka[i+1].get_ID());
        tab_temp[i].set_waga(paczka[i+1].get_waga());
    }

    for(int i=0; i<(size-1); i++)
        paczka[i] = tab_temp[i];

    paczka=tab_temp;
}

void usun_element(Paczka** &paczka, int &size, int index)
{
    Paczka **tab_temp;

    create(tab_temp, (size-1));

    for(int i=0; i<(index-1); i++)
    {
        tab_temp[i]->set_ID(paczka[i]->get_ID());
        tab_temp[i]->set_waga(paczka[i]->get_waga());
    }

    for(int i=(index-1); i<(size-1); i++)
    {
        tab_temp[i]->set_ID(paczka[i+1]->get_ID());
        tab_temp[i]->set_waga(paczka[i+1]->get_waga());
    }

    for(int i=0; i<(size-1); i++)
        (*paczka[i]) = (*tab_temp)[i];

    paczka=tab_temp;
}

void interface(Paczka* &paczka, Paczka** &paczka1)
{
    int n;
    int size;
    int index;
    int ID;
    while(n!=13)
    {
        cout<<"1 - UTWORZ TABLICE"<<endl;
        cout<<"2 - WYSWIETL TABLICE"<<endl;
        cout<<"3 - WYCZYSC TABLICE"<<endl;
        cout<<"4 - DODAJ NOWY ELEMENT"<<endl;
        cout<<"5 - USUN ELEMENT"<<endl;
        cout<<"6 - WYSWIETL PACZKE O INDEXIE"<<endl;
        cout<<"7 - STWORZ KLIENTA"<<endl;
        cout<<"8 - AGREGACJA"<<endl;
		cout<<"9 - DODAWANIE PRACOWNIKOW"<<endl;
		cout<<"10 - DODAJ PRACOWNIKA/KLIENTA DO DZIENNIKA"<<endl;
		cout<<"11 - KSIEGOWOSC"<<endl;
		cout<<"12 - POLIMORFIZM"<<endl;
		cout<<"13 - WYJDZ"<<endl;
        cout<<"WYBOR:";
        cin>>n;
        switch(n)
        {
            case 1:
            printf("PODAJ ROZMIAR TABLICY:");
            cin>>size;
            create(paczka, size);
            if(paczka==NULL)
                cout<<"PAMIEC NIE ZOSTALA PRZYDZIELONA"<<endl;
            else
                cout<<"PAMIEC ZOSTALA PRZYDZIELONA"<<endl;
            initialize(paczka, size);;

            create(paczka1, size);
            if(paczka1==NULL)
                cout<<"PAMIEC NIE ZOSTALA PRZYDZIELONA"<<endl;
            else
                cout<<"PAMIEC ZOSTALA PRZYDZIELONA"<<endl;
            initialize(paczka1, size);
            break;

            case 2:
                display(paczka, size);
                cout<<"--------------------"<<endl;
                display(paczka1, size);
            break;

            case 3:
                usun(paczka, size);
                usun(paczka1, size);
            break;

            case 4:
                cout<<"PODAJ INDEX:";
                cin>>index;
                cout<<"PODAJ ID:";
                cin>>ID;
                dodaj_nowy_element(paczka, size, index, ID);
                dodaj_nowy_element(paczka1, size, index, ID);
                size++;
            break;

            case 5:
                cout<<"PODAJ INDEX:";
                cin>>index;
                usun_element(paczka, size, index);
                usun_element(paczka1, size, index);
                size--;
            break;

            case 6:
                cout<<"PODAJ INDEX:";
                cin>>index;
                wyswietl_paczke_o_indexie(paczka1, index);
            break;

            case 7:
            {
                Dziennik::Klient klient("Adam");
                Dziennik::Klient klient2 = klient;
                cout<<klient2.get_imie()<<endl;
                cout<<klient.get_imie()<<endl;
            }
            break;

            case 8:
            {
                Zaladunek zaladunek;
				Zaladunek zaladunek2 = zaladunek;
				
            }
            break;

			case 9:
            {
              	Dziennik::Pracownik p1("Kowalski");
    			Dziennik::Pracownik p2("Nowak");
    			Dziennik::Pracownik p3("Kowalczyk");
    			Dziennik::Pracownik p4("Lewandowski");
    			Dziennik::Pracownik::pokaz_liste();
            }
            break;

			case 10:
            {
              	Dziennik::Pracownik p1("Abacki");
				Dziennik::Klient k1("Adam");
				p1.dodaj_do_dziennika();
				k1.dodaj_do_dziennika();
            }
            break;

			case 11:
            {
            	Ksiegowosc acc1(1000, 500), acc2(2000, 1500), acc4;
				Ksiegowosc acc3=acc1+acc2;
				acc3.print_dodaj();
				acc3.print_odejmij();
				cout<<acc1;
				cin>>acc4;
				cout<<acc4;
				acc1=acc2;
				cout<<acc1;
				cout<<acc1[5]<<endl;
				cout<<acc1(500, 600, 700)<<endl;
            }
            break;
			
			case 12:
			{
				Pojazd *tab[3];
				tab[0] = new Samochod("Szczecin");
				tab[1] = new Van("Warszawa", "Mazowieckie");
				tab[2] = new Samolot("Berlin", "Niemcy", "Europa");
				for(int i=0; i<3; i++)
					tab[i]->dostarcz_paczke();
			}
			break;

        }
    }
}

int main()
{
    Paczka *paczka;
    Paczka **paczka1;
    interface(paczka, paczka1);
    return 0;
}

