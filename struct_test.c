#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct strukturka{
	int var1;
	int var2;
	int var3;
	int var4;
	int *ptr1;
}strukturka;



int main()
{
	printf("HELLO\n");
	strukturka strct;
	int var = 80;
	strct.var1 = 5;
	strct.var2 = 10;
	strct.var3 = 15;
	strct.var4 = 20;
	strct.ptr1 = &var;
	printf("SIZE: %ld\n", sizeof(strct));
	//int* ptr;
	//ptr = &strct.var1;
	//printf("VAL: %d %d %d %d\n", ptr, ptr+1, ptr+2, ptr+3);
	return 0;
}
