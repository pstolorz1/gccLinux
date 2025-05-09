#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct structure
{
    int i;
    char c;
    float f;
};

struct structure** randVals(int N)
{
    //Allocate array of structures on heap
    struct structure** tab = (struct structure**)malloc(sizeof(struct structure*) * N);
    for (int i = 0; i < N; i++)
        tab[i] = (struct structure*)malloc(sizeof(struct structure));

    int tab1[10001];
    for(int i = 0; i < 10001; i++)
        tab1[i] = i-1000;
    
    //Random values
    srand(time(NULL));
    for(int i = 10000; i > 0; i--)
    {
        int r = rand()%i;
        int temp = tab1[i];
        tab1[i] = tab1[r];
        tab1[r] = temp;
    }
    
    //Set structure fields
    for (int i = 0; i < N; i++)
    {
        tab[i]->i = tab1[i];
        tab[i]->c = "BCDEFGHIJKLMNOPQRSTUVWX"[rand() % 23];
        tab[i]->f = 1000 + i;
    }
    
    return(tab);
}

void delete(struct structure **tab, int N)
{
    for(int i = 0; i < N; i++)
        free(tab[i]);
    free(tab);
}

void sort(struct structure **tab, int N)
{
    for(int i = 1; i < N-1; i++)
    {
        for(int j = 1; j < N-i; j++)
        {
            if(tab[j-1]->i > tab[j]->i)
            {
                struct structure *temp = tab[j-1];
                tab[j-1] = tab[j];
                tab[j] = temp;
            }
        }
    }
}

int countSigns(struct structure **tab, int N, char X)
{
    int counter = 0;
    for(int i = 0; i < N; i++)
    {
        if(tab[i]->c == X)
            counter++;
    }
    return(counter);
}

void display(struct structure **tab, int n)
{
    for(int i = 0; i < n; i++)
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
    struct structure **tab;
    tab = randVals(N);
    sort(tab, N);
    display(tab, 20);
    printf("CHAR COUNTER %c = %d\n", X, countSigns(tab, N, X));
    delete(tab, N);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("TIME = %f\n", time_spent);

    return 0;
}
