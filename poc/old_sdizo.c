//SDIZO I1 214B LAB02
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


double losuj(double low,double high)
{
    return((double)rand()*(high-low))/(double)RAND_MAX+low;
}

struct node *create(int a)
{
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->a=a;
    newNode->b=losuj(-1, 1);
    newNode->c='T';
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
};

void insert(struct node** head, struct node* newNode)
{
    struct node* temp;

    if (*head == NULL)
        *head = newNode;

    else if ((*head)->a >= newNode->a)
    {
        newNode->next = *head;
        newNode->next->prev = newNode;
        *head = newNode;
    }

    else
    {
        temp = *head;

        // lokalizuje gdzie wstawic nowy wezel
        while (temp->next != NULL && temp->next->a < newNode->a)
            temp = temp->next;

        newNode->next = temp->next;

        // jezeli nowy wezel nie jest wstawiony na koncu
        if (temp->next != NULL)
            newNode->next->prev = newNode;

        temp->next = newNode;
        newNode->prev = temp;
    }
}

void insert2(struct node** head, int n)
{
    int i, r, temp1;
    int tab1[99901];
    for(i=0; i<99901; i++)
        tab1[i] = i+99;
    srand(time(NULL));
    for(i=99900; i>0; i--) //Algorytm Fisher–Yatesa
    {
        r = rand()%i;
        temp1 = tab1[i];
        tab1[i] = tab1[r];
        tab1[r] = temp1;
    }
    for(i=0; i<n; i++)
    {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->a=tab1[i];
    newNode->b=losuj(-1, 1);
    newNode->c='T';
    newNode->prev = NULL;
    newNode->next = NULL;


    struct node* temp;

    if (*head == NULL)
        *head = newNode;

    else if ((*head)->a >= newNode->a)
    {
        newNode->next = *head;
        newNode->next->prev = newNode;
        *head = newNode;
    }

    else
    {
        temp = *head;

        // lokalizuje gdzie wstawic nowy wezel
        while (temp->next != NULL && temp->next->a < newNode->a)
            temp = temp->next;

        newNode->next = temp->next;

        // jezeli nowy wezel nie jest wstawiony na koncu
        if (temp->next != NULL)
            newNode->next->prev = newNode;

        temp->next = newNode;
        newNode->prev = temp;
    }
    }
}

void search(struct node** head, int x)
{
    struct node* current = head;
    int y=0;
    while (current != NULL)
    {
        if (current->a == x)
        {
            printf("Znaleziono szukany element: \n");
            printf("%d\n", current->a);
            printf("%f\n", current->b);
            printf("%c\n", current->c);
            y=1;
        }
        current = current->next;
    }
    if(y=0);
        printf("Nie znaleziono szukanego elementu\n");
}

int length(struct node* head)
{
    int d = 0;
    struct node* temp = head;
    while(temp != NULL)
    {
        d++;
        temp = temp->next;
    }
    printf("liczba wezlow wynosi: %d\n", d);
    return d;
}

void printList(struct node* head)
{
    while (head != NULL)
    {
        printf("%d\n", head->a);
        printf("%f\n", head->b);
        printf("%c\n", head->c);
        head = head->next;
    }
}

void display_first(struct node* head, int z)
{
    int i=0;
    while (head != NULL && i<z)
    {
        printf("%d\n", head->a);
        head=head->next;
        i++;
    }
}

void display_last(struct node* head, int z)
{
    int i=0;
    int j;
    int g;
    int h;
    int l=length(head);
    int *tab1;
    int *tab2;
    tab1 = (int*) malloc((l) * sizeof(int));
    tab2 = (int*) malloc((l) * sizeof(int));
    while(head != NULL && i<l)
    {
      tab1[i]=head->a;
      head = head->next;
      i++;
    }
    for(j=0; j<=l; j++)
        tab2[j]=tab1[l-1-j];
    if(l>=z)
    {
        for(g=0; g<=z; g++)
            printf("%d\n", tab2[g]);
    }
    if(l<z)
    {
        for(h=0; h<=l; h++)
            printf("%d\n", tab2[h]);
    }
}

void delete1(struct node** head, int z)
{
   struct node* tmp = head;
   if(tmp->a == z)
   {
        tmp = tmp->next;
        free(tmp);
        return;
   }

   struct node* last = head;
   while((tmp = tmp->next) != NULL)
   {
        if(tmp->a == z)
        {
         last->next = tmp->next;
         free(tmp);
         return;
        }
      last = tmp;
   }
}

void deleteHead(struct node **head, struct node *del)
{
  *head = del->next;
  free(del);
  return;
}

void deleteList(struct node** head)
{
    		struct node *iter = head, *temp;
    		while(iter != NULL) //dopoki lista nie jest pusta
    		{
    			temp = iter; //obecny wezel
    			iter = iter->next; //nastepny wezel

    			if(temp->prev)
    				temp->prev = NULL;
    			if(temp->next)
    				temp->next = NULL;
    		}
}

int main()
{
    clock_t begin, end;
    double time_spent;
    begin = clock();

    FILE* fp = fopen("inlab02.txt", "r");
    if (fp == NULL)
        return -1;
    int X, k1, k2, k3, k4, k5;
    fscanf (fp, "%d %d %d %d %d %d", &X, &k1, &k2, &k3, &k4, &k5);
    fclose(fp);

    // pusta lista
    struct node* head = NULL;
    struct node* new_node;

    search(head, k1);
    insert2(&head, X);
    length(head);
    display_first(head, 20);
    new_node = create(k2);
    insert(&head, new_node);
    display_first(head, 20);
    new_node = create(k3);
    insert(&head, new_node);
    display_first(head, 20);
    new_node = create(k4);
    insert(&head, new_node);
    display_first(head, 20);
    new_node = create(k5);
    insert(&head, new_node);
    delete1(head, k3);
    display_first(head, 20);
    delete1(head, k2);
    display_first(head, 20);
    delete1(head, k5);
    length(head);
    search(head, k5);
    display_last(head, 11);
    deleteList(head);
    deleteHead(&head, head);
    //display_last(head, 11);
    length(head);

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f", time_spent);

    getch();
    return 0;
}

