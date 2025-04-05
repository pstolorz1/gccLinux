//SDIZO I1 234A LAB03
//Pawe³ Stolorz
//sp39443@zut.edu.pl

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

struct node
{
    int klucz;
    struct node *left;
    struct node *right;
    char tab[10];
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
            printf("ELEMENT %d JUZ SIE ZNAJDUJE W DRZEWIE\n", curr->klucz);
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

int insert_rand(struct node *&root, int x)
{
    int i, r, temp;
    int tab1[20001];
    for(i=0; i<20001; i++)
        tab1[i] = i-10000;
    srand(time(NULL));
    for(i=20000; i>0; i--)
    {
        r = rand()%i;
        temp = tab1[i];
        tab1[i] = tab1[r];
        tab1[r] = temp;
    }

    for(i=0; i<x; i++)
    {
    struct node* new_node = new struct node;
    new_node->left = NULL;
	new_node->right = NULL;
	new_node->klucz = tab1[i];
	// przechowuje rodzica aktualnego wezla
	struct node *parent = NULL;
	 // startujemy z roota
	struct node *curr = root;
	// przegladamy drzewo, znajdujemy rodzica i duplikat
	while (curr != NULL)
	{
	    if(curr->klucz==tab1[i])
        {
            printf("ELEMENT %d JUZ SIE ZNAJDUJE W DRZEWIE\n", curr->klucz);
            return(-1);
        }
	    // update parent node as current node
		parent = curr;
        // if given key is less than the current node, go to left subtree
        // else go to right subtree
        if (curr->klucz>tab1[i])
			curr = curr->left;
		else
			curr = curr->right;
	}
	//wstawianie do drzewa
	if (root == NULL)
		root = new_node;
	else if (parent->klucz>tab1[i])
		parent->left = new_node;
	else
		parent->right = new_node;
    }
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
    if(flag==1)
        printf("ZNALEZIONO ELEMENT %d\n", p->klucz);
    else
        printf("ELEMENT %d NIE ISTNIEJE\n", x);
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
        printf("ELEMENT DO SKASOWANIA NIE ISTNIEJE\n");
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

void preorder(struct node *root)
{
	if (root != NULL)
    {
        printf("%d\n", root->klucz);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(struct node *root)
{
	if (root != NULL)
    {
        inorder(root->left);
        printf("%d\n", root->klucz);
        inorder(root->right);
    }
}

void postorder(struct node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d\n", root->klucz);
    }
}

int main()
{
    FILE* fp = fopen("inlab03.txt", "r");
    if (fp == NULL)
        return -1;
    int X, k1, k2, k3, k4;
    fscanf (fp, "%d %d %d %d %d", &X, &k1, &k2, &k3, &k4);
    fclose(fp);

    clock_t begin, end;
    double time_spent;
    begin = clock();

    struct node *root=NULL;

    remove(root, k1);
    printf("\n");
    insert(root, k1);
    insert_rand(root, X);

    printf("INORDER\n");
    inorder(root);
    printf("LICZBA ELEMENTOW WYNOSI %d\n", count(root));
    printf("\n");
    printf("PREORDER\n");
    preorder(root);
    printf("LICZBA ELEMENTOW WYNOSI %d\n", count(root));
    printf("\n");

    insert(root, k2);
    printf("INORDER\n");
    inorder(root);
    printf("LICZBA ELEMENTOW WYNOSI %d\n", count(root));
    printf("\n");

    insert(root, k3);
    insert(root, k4);

    remove(root, k1);
    printf("PREORDER\n");
    preorder(root);
    printf("LICZBA ELEMENTOW WYNOSI %d\n", count(root));
    printf("\n");
    search(root, k1);
    printf("\n");

    remove(root, k2);
    printf("INORDER\n");
    inorder(root);
    printf("LICZBA ELEMENTOW WYNOSI %d\n", count(root));
    printf("\n");

    remove(root, k3);
    remove(root, k4);
    printf("LICZBA ELEMENTOW WYNOSI %d\n", count(root));

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f", time_spent);
    getchar();
    return 0;
}
