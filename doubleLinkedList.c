//SDIZO I1 234A LAB02
//Paweł Stolorz
//sp39443@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int a;
    double b;
    char c;
    struct node *next;
    struct node *prev;
};

void insert_node(struct node **head, int x)
{
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->a = x;
    newNode->b = rand()*(100.0)/(double)RAND_MAX;
    newNode->c = 'T';

    // PUSTA LISTA
    if (*head == NULL)
    {
        newNode->next = newNode;
        newNode->prev = newNode;
        *head = newNode;
        return;
    }

    // ELEMENT MNIEJSZY NIZ HEAD
    else if ((*head)->a > newNode->a)
    {
        struct node *temp = (*head)->prev;
        newNode->next = *head;
        newNode->prev = temp;
        temp->next = newNode;
        (*head)->prev = newNode;
        *head = newNode;
        return;
    }

    // SZUKAMY MIEJSCA W LISCIE
    else
    {
        struct node *temp = *head;
        while (temp->next != *head && temp->next->a < newNode->a)
            temp = temp->next;
        if(temp->next->a==x)
        {
            printf("W LISCIE JEST JUZ TEN ELEMENT");
            return;
        }
        newNode->next = temp->next;
        newNode->next->prev = newNode;
        temp->next = newNode;
        newNode->prev = temp;
        return;
    }
}

void insert_rand(struct node **head, int x)
{
    int tab_temp[99901];
    for(int i=0; i<99901; i++)
        tab_temp[i] = i+99;
    srand(time(NULL));
    for(int i=99900; i>0; i--)
    {
        int r = rand()%i;
        int temp = tab_temp[i];
        tab_temp[i] = tab_temp[r];
        tab_temp[r] = temp;
    }
    for(int i=0; i<x; i++)
        insert_node(head, tab_temp[i]);
}

void search_node(struct node *head, int x)
{
    if(head==NULL)
    {
        printf("W LISCIE NIE MA ZADNYCH ELEMENTOW\n");
        return;
    }
    struct node *temp = head;

    do
    {
        if (temp->a == x)
        {
            printf("Znaleziono szukany element: ");
            printf("%d ", temp->a);
            printf("%f ", temp->b);
            printf("%c\n", temp->c);
            return;
        }
        temp = temp->next;
    }
    while (temp != head);
    printf("NIE ZNALEZIONO ELEMENTU: %d\n", x);
    return;
}

void delete_node(struct node **head, int z)
{
    //PUSTA LISTA
    if (*head == NULL)
    {
        printf("W LISCIE NIE MA ZADNYCH ELEMENTOW\n");
        return;
    }

    struct node *temp = *head;
    struct node *prev1 = NULL;

    //SPRAWDZA CZY W LISCIE JEST TYLKO JEDEN WEZEL HEAD
    if (temp->next == *head)
    {
        *head = NULL;
        free(temp);
        return;
    }
    //JEZELI LISTA MA WIECEJ NIZ JEDEN WEZEL
    //SZUKA I SPRAWDZA CZY WEZEL JEST W LISCIE
    while (temp->a != z)
    {
        if (temp->next == *head)
        {
            printf("\nNIE ZNALEZIONO ELEMENTU: %d\n", z);
            return;
        }
        prev1 = temp;
        temp = temp -> next;
    }
    // SPRAWDZA CZY PIERWSZY, ZMIENIA HEAD
    if (temp == *head)
    {
        prev1 = (*head) -> prev;
        *head = (*head) -> next;
        prev1 -> next = *head;
        (*head) -> prev = prev1;
        free(temp);
        return;
    }
    //WEZEL JEST W SRODKU
    else
    {
        prev1->next = temp->next;
        temp->next->prev = prev1;
        free(temp);
        return;
    }
}

void display_first(struct node *head, int y)
{
    struct node *temp = head;

    if(head==NULL)
    {
        printf("W LISCIE NIE MA ZADNYCH ELEMENTOW\n");
        return;
    }

    for(int i=0; i<y; i++)
    {
        printf("%d ", temp->a);
        printf("%f ", temp->b);
        printf("%c", temp->c);
        printf("\n");
        temp = temp->next;
    }
}

void display_last(struct node *head, int z)
{
    struct node *temp = head;

    if(head==NULL)
    {
        printf("W LISCIE NIE MA ZADNYCH ELEMENTOW\n");
        return;
    }

    for(int i=0; i<z; i++)
    {
        temp = temp->prev;
        printf("%d ", temp->a);
        printf("%f ", temp->b);
        printf("%c", temp->c);
        printf("\n");
    }
}

void number_of_nodes(struct node *head)
{
    struct node *temp = head;
    int counter = 0;

    if(head==NULL)
    {
        printf("W LISCIE NIE MA ZADNYCH ELEMENTOW\n");
        return;
    }

    do
    {
        counter++;
        temp = temp->next;
    }
    while (temp != head);

    printf("W LISCIE ZNAJDUJE SIE %d ELEMENTOW\n", counter);
}

void delete_all(struct node **head)
{
    struct node *temp = *head;
    if(*head==NULL)
    {
        printf("W LISCIE NIE MA ZADNYCH ELEMENTOW\n");
        return;
    }
    while((*head)!=NULL)
    {
        temp=temp->next;
        delete_node(head, temp->a);
    }
}

int main()
{
    clock_t begin, end;
    double time_spent;
    begin = clock();
    int X = 2001, k1 = 13666, k2 = 4, k3 = 7, k4 = -1, k5 = 100001;
    
    struct node* head = NULL;
    
    printf("START DATA: %d, %d, %d, %d, %d, %d\n", X, k1, k2, k3, k4, k5);
    search_node(head, k1);
    insert_rand(&head, X);
    number_of_nodes(head);
    display_first(head, 20);
    printf("\n -------------------- \n\n");
    insert_node(&head, k2);
    display_first(head, 20);
    printf("\n -------------------- \n\n");
    insert_node(&head, k3);
    display_first(head, 20);
    printf("\n -------------------- \n\n");
    insert_node(&head, k4);
    display_first(head, 20);
    printf("\n -------------------- \n\n");
    insert_node(&head, k5);
    display_last(head, 11);
    printf("\n -------------------- \n\n");
    delete_node(&head, k3);
    display_first(head, 20);
    printf("\n -------------------- \n\n");
    delete_node(&head, k2);
    display_first(head, 20);
    printf("\n -------------------- \n\n");
    delete_node(&head, k5);
    number_of_nodes(head);
    display_last(head, 11);
    printf("\n -------------------- \n\n");
    search_node(head, k5);
    display_last(head, 11);
    printf("\n -------------------- \n\n");
    delete_all(&head);
    display_last(head, 11);
    printf("\n -------------------- \n\n");
    number_of_nodes(head);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("CZAS WYKONANIA:%f\n", time_spent);
    //getchar();
    return 0;
}


