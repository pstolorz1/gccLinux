#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define uint8 unsigned char

typedef struct node
{
  int a;
  unsigned char b;
  struct node *next;
}node;

void add(node **nodes, int aVal, unsigned char bVal)
{
  node *newNode = (node*)malloc(sizeof(node));
  newNode->a = aVal;
  newNode->b = bVal;
  if(*nodes == NULL)
  {
    newNode -> next = *nodes;
    *nodes = newNode;
  }
  else
  {
    node *temp = *nodes;
    newNode -> next = temp->next;
    temp->next = newNode;
  }
  
}

void printNodes(node *nodes)
{
  while(nodes != NULL)
  {
    printf("a: %d, b: %d\n", nodes->a, nodes->b);
    nodes = nodes->next;
  }
}

int main()
{
  node *head = NULL;
  add(&head, 10, 5);
  add(&head, 50, 10);
  add(&head, 100, 75);
  add(&head, 200, 175);
  printNodes(head);
  free(head);
  return 0;
}
