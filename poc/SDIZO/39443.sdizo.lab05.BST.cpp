//SDIZO I1 234A LAB05
//Pawe³ Stolorz
//sp39443@zut.edu.pl

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

using namespace std;

struct node
{
    int klucz;
    struct node *left;
    struct node *right;
};

int insert(struct node *&root, int x)
{
    struct node* new_node = new struct node;
    new_node->left = NULL;
	new_node->right = NULL;
	new_node->klucz = x;
	// przechowuje rodzica aktualnego wezla
	struct node *parent = NULL;
	 // startujemy z roota
	struct node *curr = root;
	// przegladamy drzewo, znajdujemy rodzica i ew. duplikat
	while (curr != NULL)
	{
	    if(curr->klucz==x)
        {
            //printf("ELEMENT %d JUZ SIE ZNAJDUJE W DRZEWIE\n", curr->klucz);
            return(-1);
          }
	    // rodzic jest obecnym wezlem
		parent = curr;
		// jezeli klucz jest mniejszy niz obecny wezel idz do lewego poddrzewa
		// przeciwnie idz do prawego
        if (curr->klucz>x)
			curr = curr->left;
		else
			curr = curr->right;
	}
	//wstawianie do drzewa
	if (root == NULL)
		root = new_node;
	else if (parent->klucz>x)
		parent->left = new_node;
	else
		parent->right = new_node;
    return(0);
}

int search(struct node *root, int x)
{
    int flag = 0;
    struct node *p = root;
    while((p!=NULL) && flag==0)
    {
        if(x==p->klucz)
        {
            flag = 1;
        }
        else if(p->klucz<x)
            p=p->right;
        else
            p=p->left;
    }
   // if(flag==1)
   //     printf("ZNALEZIONO ELEMENT %d\n", p->klucz);
   // else
       // printf("ELEMENT %d NIE ISTNIEJE\n", x);
    return(0);
}

int remove(struct node *&root, int x)
{
    struct node *parent = NULL;
    struct node *curr = root;
    while((curr!=NULL) && (x!=curr->klucz)) //szukamy danego wezla
    {
        parent=curr;
        if(curr->klucz<x)
            curr=curr->right;
        else
            curr=curr->left;
    }
    if(curr==NULL)
    {
       // printf("ELEMENT DO SKASOWANIA NIE ISTNIEJE\n");
        return(-1);
    }
    if((curr->right==NULL) && (curr->left==NULL)) //usuwany wezel jest lisciem
    {
        if(curr==root)
        {
            root=NULL; //usuwany lisc jest takze korzeniem
            return(0);
        }
        if(parent->right==curr)
            parent->right=NULL;
        else
            parent->left=NULL;
        return(0);
    }
    if(curr->right==NULL) //usuwany wezel ma tylko lewe poddrzewo
    {
        if(curr==root)
            root=curr->left;
        else if(parent->right==curr)
            parent->right=curr->left;
        else
            parent->left=curr->left;
        return(0);
    }
    if(curr->left==NULL) //usuwany wezel ma tylko prawe poddrzewo
    {
        if(curr==root)
            root=curr->right;
        else if(parent->right==curr)
            parent->right=curr->right;
        else
            parent->left=curr->right;
        return(0);
    }
    //usuwany wêze³ ma oba poddrzewa
    //odwo³anie sie do poprzednika, czyli najwiekszego klucza w lewym poddrzewie
    struct node *preparent = curr;
    struct node *child = curr->left;
    while(child->right!=NULL)
    {
        preparent = child;
        child = child->right;
    }
    if(child==curr->left) //poprzednik jest lewym potomkiem usuwanego wêz³a
    {
        if(curr==root)
            root=curr->left;
        else if (parent->right == curr)
            parent->right = child;
        else
            parent->left = child;
        return(0);
    }
    //poprzednik nie jest lewym potomkiem wezla, lecz jego wnukiem lub prawnukiem
    struct node *grandchild = child->left;//ewentualny potomek poprzednika
    //adopcja potomstwa poprzednika przez jego rodzica
    if (preparent->right == child)
        preparent->right = grandchild;
    else
        preparent->left = grandchild;
    //adopcja potomstwa usuwanego wêz³a przez jego poprzednika
    child->left = curr->left;
    child->right = curr->right;
    //adopcja poprzednika przez rodzica usuwanego wêz³a
    if(curr==root)
        root=child;
    else if (parent->right == curr)
        parent->right = child;
    else
        parent->left = child;
    return(0);
}

int count(struct node *root)
{
    int counter = 1;
    if (root == NULL)
        return 0;
    else
    {
        counter += count(root->left);
        counter += count(root->right);
        return counter;
     }
}

void inorder(struct node *root)
{
	if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->klucz);
        inorder(root->right);
    }
}

int main()
{
    // pusta lista
    struct node *root = NULL;

    int i;
    int N;
    int przelacznik;

    printf("PODAJ N: ");
    scanf("%d", &N);

    printf("---WSTAWIANIE---\n");
    printf("1 - ROZKLAD LOSOWY\n");
    printf("2 - NA PRZEMIAN WARTOSC LOSOWA I LICZBA NATURALNA\n");
    printf("WYBOR: ");
    scanf("%d", &przelacznik);

    clock_t begin, end;
    double time_spent_1;
    begin = clock();

    srand(1);

    switch(przelacznik)
    {
        case 1:
            for(i=1; i<=N; i++)
                insert(root, rand());
        break;

        case 2:
            for(i=1; i<=N/2; i++)
            {
                insert(root, rand());
                insert(root, i);
            }
        break;
    }

    end = clock();
    time_spent_1 = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("CZAS WSTAWIENIA DLA %d ELEMENTOW: %f\n", N, time_spent_1);

    double time_spent_2;
    begin = clock();

    srand(2);

    for(i=1; i<=N; i++)
        search(root, rand());

    end = clock();
    time_spent_2 = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("CZAS WYSZUKANIA DLA %d ELEMENTOW: %f\n", N, time_spent_2);

    double time_spent_3;
    begin = clock();

    srand(3);

    for(i=1; i<=N; i++)
        remove(root, rand());

    end = clock();
    time_spent_3 = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("CZAS USUWANIA DLA %d ELEMENTOW: %f\n", N, time_spent_3);

    getch();
    return 0;
}
