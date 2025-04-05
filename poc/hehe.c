#include <stdio.h>
#include <stdlib.h>

void incr(int *a)
{
  printf("%d z funkcji\n", a);
}

int main()
{
  int *ptr1;
  int **ptr2;
  int var = 10;
  
  ptr1 = &var;
  ptr2 = &ptr1;
  **ptr2 = 15;
  
  //incr(&var);
  
  printf("%d\n", *(&var));
  return 0;
}
