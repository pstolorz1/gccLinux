#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* toLower(char *c)
{
  char* chLower = (char *)malloc(sizeof(char) * strlen(c));
  strcpy(chLower, c);
  char* ch = &chLower[0];
  
  while(*ch != '\0')
  {
    if(*ch >= 65 && *ch <= 90)
      *ch += 32;
    
    ++ch;
  }
  
  return chLower;
}

int main()
{
  char str[] = "SONY Microphone xD";
  printf("ORIGINAL STRING: %s\n", str);
  char* ch = toLower(str);
  printf("LOWER STRING: %s\n", ch);
  
  return 0;
}
