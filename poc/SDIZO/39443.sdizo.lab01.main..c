//SDIZO I1 234A LAB01
//Paweł Stolorz
//sp39443@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Struktura
{
    int i;
    char c;
    float f;
};

int losowanie(int N)
{
    int i, r, temp;
    struct Struktura** tab = (struct Struktura**) malloc(N * sizeof(struct Struktura*)); //alokowanie tablicy struktur
    for (i=0; i<N; i++)
        tab[i] = (struct Struktura*) malloc(sizeof(struct Struktura));

    int tab1[10001];
    for(i=0; i<10001; i++)
        tab1[i] = i-1000;
    srand(time(NULL));
    for(i=10000; i>0; i--) //losowe N
    {
        r = rand()%i;
        temp = tab1[i];
        tab1[i] = tab1[r];
        tab1[r] = temp;
    }
    for (i=0; i<N; i++) //przypisywanie wartosci
    {
        tab[i]->i=tab1[i];
        tab[i]->c = "BCDEFGHIJKLMNOPQRSTUVWX"[rand() % 23];
        tab[i]->f = 1000 + i;
    }
    return(tab);
}

void kasowanie(struct Struktura *tab[], int N)
{
    int i;
    for(i=0; i<N; i++)
        free(tab[i]);
    free(tab);
}

int sortowanie(struct Struktura *tab[], int N)
{
    int i, j;
    int flag;
    for(i=1; i<N-1; i++)
    {
        flag = 0;
        for(j=1; j<N-i; j++)
        {
            if(tab[j-1]->i > tab[j]->i)
            {
                int temp = tab[j-1];
                tab[j-1] = tab[j];
                tab[j] = temp;
                flag = 1;
            }
        }
        if(flag==0)
        return(tab);
    }
    return(tab);
}

int zliczanie_znakow(struct Struktura *tab[], int N, char X)
{
    int i;
    int licznik=0;
    for(i=0; i<N; i++)
    {
        if(tab[i]->c==X)
            licznik=licznik+1;
    }
    return(licznik);
}

void wyswietl(struct Struktura *tab[], int N)
{
    int i;
    for(i = 0; i < 20; i++)
    {
        printf("%d ", tab[i]->i);
        printf("%c ", tab[i]->c);
        printf("%f\n", tab[i]->f);
    }
}

int main()
{
    clock_t begin, end;
    double time_spent;
    begin = clock();
    int N;
    char X;
    FILE* fp = fopen("inlab01.txt", "r");
    if (fp == NULL)
        return -1;
    fscanf (fp, "%d %c", &N, &X);
    fclose(fp);
    struct Struktura *tab;
    tab=losowanie(N);
    sortowanie(tab, N);
    wyswietl(tab, N);
    printf("ilosc znakow %c = %d\n", X, zliczanie_znakow(tab, N, X));
    kasowanie(tab, N);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("CZAS = %f", time_spent);
    getchar();
    return 0;
}
