#include <stdio.h>
#include <stdlib.h>

int val_g = 0;

void test()
{
	int a = 0;
	int b =0;
	printf("task stack1 address: 0X%x\n",&a);
	printf("task stack2 address: 0X%x\n",&b);
}

void(*fp)();

int main()
{
	int a = 10;
	int *heap = malloc(sizeof(int));
	fp = test;
	printf("code address : 0X%x\n",fp);	
	printf("data address: 0X%x\n",&val_g);
	printf("heap address: 0X%x\n",heap);
	printf("main stack0 address: 0X%x\n",&a);
	fp();
	return 0;
}
