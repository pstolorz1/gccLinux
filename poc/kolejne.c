#include <stdio.h>
#include <string.h>
#define F00 0x0010
int first_var;
int* second_var;

int foo(int x)
{
  return(x*2+2);
}

void testFoo(int var, int (*funkcja)(int))
{
  printf("%d\n", funkcja(var));
}

int main()
{
  //int variable = 7;
  //testFoo(variable, foo);
  
  //char str1[16] = "hello world";
  char str2[] = "hello world";
  //char *str3 = "XD";
  
  int size = strlen(str2);
  
  char help[size];
  
  help[size] = '\0';
  
  for(int i = 0; i < strlen(str2); i++)
  {
    if(str2[strlen(str2) - 1 - i] != "/0")
      help[i] = str2[strlen(str2) - 1 - i];
  }
    
  printf("%s\n", help);
  
  //char *ptr = &str1[0];
  //printf("%c", *ptr);
  
  //while(*ptr != "/0");
  //{
  //  printf("%c", *ptr);
  //  ptr++;
  //}
  
  //for(int i = 0; i < 10; i++)
  //{
  //  printf("%s", ptr--);
  //}
  
  //printf("SIZES: %ld, %ld, %ld\n", sizeof(str1), sizeof(str2), sizeof(str3)); //16, 14, 14
  //str1[12] = 'x';
  //printf("%s\n", str3);
  return 0;
}
