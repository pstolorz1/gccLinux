#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int arrStack[8] = {1, 2, 3, 4, 5, 6};
  int *arrHeap = (int *)malloc(sizeof(int) * 8);
  
  //memcpy(arrHeap, arrStack, sizeof(int) * 8);
  
  for(int i = 0; i < 8; i++)
  {
    *arrHeap = arrStack[i];
    arrHeap++;
  }
  
  arrHeap = arrHeap - 8;
  
  for(int i = 0; i < 8; i++)
  {
    printf("%d\n", arrHeap[i]);
  }
  
  return 0;
}
