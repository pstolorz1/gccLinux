#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define uint16 unsigned short

void reverseEndianess(uint16* ex)
{
  uint16 tmp = *ex;
  *ex = (tmp << 8) | (tmp >> 8);
}

int main()
{
  uint16 var = 0b0000001111111111;
  reverseEndianess(&var);
  
  printf("VAR: %d\n", var);
  
  return 0;
}
