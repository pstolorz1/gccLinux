#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define uint8 unsigned char

uint8 zeroByte(uint8 *u8Var, uint8 pos)
{
  return(*u8Var & 1<<pos);
}

typedef union un
{
  int a;
  unsigned char b;
};

static int a = 0;

int main()
{
  uint8 var = 0b1111111;
  printf("VAR: %d\n", zeroByte(&var, 3));
  uint8 *ptr = (uint8*)malloc(sizeof(sizeof(uint8) * 8));
  free(ptr);
  
  //execl();
  //pid_t value = vfork();
  
  a++;
  printf("%d\n", a);

  if(value == 0)
  {
    printf("WITAM POTOMKA XD\n");
    printf("PID RODZICA: %d\n", getppid());
  }
  
  return 0;
}
