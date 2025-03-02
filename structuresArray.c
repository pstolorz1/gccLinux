#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Struktura
{
    int i;
    char c;
    float f;
};

struct Struktura **losowanie(int N)
{
    //alokowanie tablicy struktur
    struct Struktura **tab = (struct Struktura**)malloc(sizeof(struct Struktura*) * N);
    for (int i = 0; i < N; i++)
        tab[i] = (struct Struktura*)malloc(sizeof(struct Struktura));

    int tab1[10001];
    for(int i = 0; i < 10001; i++)
        tab1[i] = i-1000;
    
    //losowe N
    srand(time(NULL));
    for(int i = 10000; i > 0; i--)
    {
        int r = rand()%i;
        int temp = tab1[i];
        tab1[i] = tab1[r];
        tab1[r] = temp;
    }
    
    //przypisywanie wartosci
    for (int i = 0; i < N; i++)
    {
        tab[i]->i = tab1[i];
        tab[i]->c = "BCDEFGHIJKLMNOPQRSTUVWX"[rand() % 23];
        tab[i]->f = 1000 + i;
    }
    
    return(tab);
}

void kasowanie(struct Struktura **tab, int N)
{
    for(int i = 0; i < N; i++)
        free(tab[i]);
    free(tab);
}

void sortowanie(struct Struktura **tab, int N)
{
    for(int i = 1; i < N-1; i++)
    {
        for(int j = 1; j < N-i; j++)
        {
            if(tab[j-1]->i > tab[j]->i)
            {
                struct Struktura *temp = tab[j-1];
                tab[j-1] = tab[j];
                tab[j] = temp;
            }
        }
    }
}

int zliczanie_znakow(struct Struktura **tab, int N, char X)
{
    int licznik = 0;
    for(int i = 0; i < N; i++)
    {
        if(tab[i]->c == X)
            licznik++;
    }
    return(licznik);
}

void wyswietl(struct Struktura **tab, int N)
{
    for(int i = 0; i < 20; i++)
        printf("%d %c %f\n", tab[i]->i, tab[i]->c, tab[i]->f);
}

int main()
{
    clock_t begin, end;
    double time_spent;
    begin = clock();
    
    int N = 7777;
    char X = 'T';
    
    printf("START DATA: %d, %c\n", N, X);
    struct Struktura **tab;
    tab = losowanie(N);
    sortowanie(tab, N);
    wyswietl(tab, N);
    printf("ilosc znakow %c = %d\n", X, zliczanie_znakow(tab, N, X));
    kasowanie(tab, N);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("CZAS = %f\n", time_spent);
    //getchar();
    return 0;
}

