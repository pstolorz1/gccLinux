#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uint8 unsigned char
#define STACK_SIZE 8

int main()
{
  uint8 arrStack[STACK_SIZE] = {0, 1, 7, 100, 105, 200, 250, 255};
  uint8* arrHeap = (uint8*)malloc(sizeof(uint8) * STACK_SIZE);
  
  if(arrHeap != NULL)
  {
    //memcpy(arrHeap, arrStack, sizeof(int) * STACK_SIZE);
    
    //Manual copying array from stack to heap
    uint8* arrHeapTmp = arrHeap;

    for(int i = 0; i < STACK_SIZE ; i++)
      *arrHeapTmp++ = arrStack[i];
    
    for(int i = 0; i < STACK_SIZE; i++)
      printf("%d\n", arrHeap[i]);

    free(arrHeap);
  }
  else
  {
    return -1;
  }
  
  return 0;
}
