#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

void _malloc()
{
	char* mp = (char*)malloc(10);
	memset(mp,'1',sizeof(char)*10);
	if(mp != NULL){
		printf("_malloc : %s\n",mp);
	}
	free(mp);
}

void _calloc()
{
	int* ap = (int*)calloc(10,sizeof(int));
	if(ap != NULL){
		int i = 0;
		while(i < 10){
			printf("%d ",ap[i++]);
		}
	}else{
		printf("calloc error!\n");
	}
	printf("\n");
	free(ap);
}

void _realloc()
{
	char* mp =(char*)malloc(10);
	if(mp != NULL){
		memset(mp,'0',sizeof(char)*10);
		printf("%s\n",mp);
	}else{
		printf("malloc error!\n");
	}
	mp = realloc(mp,11 + sizeof(char)*10);
	if(mp != NULL){
	
	//	memset(mp,'1',sizeof(char)*20);
		printf("%s\n",mp);
	}else{
		printf("realloc error!\n");
	}
	free(mp);
}

int main()
{
	_malloc();
	_calloc();
	_realloc();
	return 0;
}
