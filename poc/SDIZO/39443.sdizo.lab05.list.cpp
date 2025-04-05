//SDIZO I1 234A LAB05
//Paweł Stolorz
//sp39443@zut.edu.pl

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

using namespace std;

struct node
{
    int a;
    struct node *next;
    struct node *prev;
};

void insert(struct node **head, int x)
{
    struct node *newNode = new struct node;
    newNode->a = x;

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
            //printf("W LISCIE JEST JUZ TEN ELEMENT");
            return;
        }
        newNode->next = temp->next;
        newNode->next->prev = newNode;
        temp->next = newNode;
        newNode->prev = temp;
        return;
    }
}

void search(struct node **head, int x)
{
    struct node *temp = *head;

    do
    {
        if (temp->a == x)
        {
            //printf("Znaleziono szukany element: ");
           // printf("%d\n", curr->a);
            return;
        }
        temp = temp->next;
    }
    while (temp != *head);
    //printf("NIE ZNALEZIONO ELEMENTU: %d\n", x);
    return;
}

void deleteNode(struct node **head, int z)
{
    //PUSTA LISTA
    if (*head == NULL)
    {
        printf("W LISCIE NIE MA ZADNYCH ELEMENTOW");
        return;
    }

    struct node *curr = *head;
    struct node *prev1 = NULL;
    //SZUKA I SPRAWDZA CZY WEZEL JEST W LISCIE
    while (curr->a != z)
    {
        if (curr->next == *head)
        {
           // printf("\nNIE ZNALEZIONO ELEMENTU: %d\n", z);
            return;
        }
        prev1 = curr;
        curr = curr -> next;
    }
    //SPRAWDZA CZY W LISCIE JEST TYLKO JEDEN WEZEL
    if (curr -> next == *head && prev1 == NULL)
    {
        (*head) = NULL;
        free(curr);
        return;
    }
    // JEZELI LISTA MA WIECEJ NIZ JEDEN WEZEL
    // SPRAWDZA CZY PIERWSZY
    if (curr == *head)
    {
        prev1 = (*head) -> prev;
        *head = (*head) -> next;
        prev1 -> next = *head;
        (*head) -> prev = prev1;
        free(curr);
        return;
    }

    // SPRAWDZA CZY OSTATNI
    else if (curr->next == *head)
    {
        prev1 -> next = *head;
        (*head) -> prev = prev1;
        free(curr);
        return;
    }
    //WEZEL JEST W SRODKU
    else
    {
        struct node *temp = curr -> next;
        prev1 -> next = temp;
        temp -> prev = prev1;
        free(curr);
        return;
    }
}

void display(struct node *head)
{
    struct node *curr = head;
    int counter = 0;

    if(head==NULL)
    {
        printf("W LISCIE NIE MA ZADNYCH ELEMENTOW\n");
        return;
    }

    do
    {
        counter++;
        //printf("%d ", curr->a);
        curr = curr->next;
    }
    while (curr != head);

    printf("WSTAWIONO %d ELEMENTOW\n", counter);
}

int main()
{
    // pusta lista
    struct node *head = NULL;

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
                insert(&head, rand());
        break;

        case 2:
            for(i=1; i<=N/2; i++)
            {
                insert(&head, rand());
                insert(&head, i);
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
        search(&head, rand());

    end = clock();
    time_spent_2 = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("CZAS WYSZUKANIA DLA %d ELEMENTOW: %f\n", N, time_spent_2);

    double time_spent_3;
    begin = clock();

    srand(3);

    for(i=1; i<=N; i++)
        deleteNode(&head, rand());

    end = clock();
    time_spent_3 = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("CZAS USUWANIA DLA %d ELEMENTOW: %f\n", N, time_spent_3);

    getch();
    return 0;
}
