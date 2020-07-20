#include<stdio.h>

void fun1()
{
	printf("fun1\n");
}

void fun2()
{
	printf("fun2\n");
}

void fun3()
{
	printf("fun3\n");
}

void main()
{
	atexit(fun1);
	atexit(fun2);
	atexit(fun3);
	printf("main\n");
}



