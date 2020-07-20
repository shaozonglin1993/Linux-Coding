#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void _malloc(char** arr, int r)
{
	*arr = (char *)malloc(sizeof(char)*r);
}

void __malloc(char** arr, int r)
{
	*arr = (char *)malloc(sizeof(char)*r);
}

void _memset(char** arr,int r)
{
	char *p = *arr;
	*arr = (char *)memset(p,'1',sizeof(char)*r);

}

int main()
{
	int r = 0, n = 0;
	printf("please input r & n\n");
	scanf("%d%d",&r,&n);
	
	int i = 0,j = 0;
	char* arr = NULL;
	_malloc(&arr,r);
	__malloc(&arr,n);
	if(NULL!=arr){
		_memset(&arr,1);
	}
	for(i = 0;i < r;i++){
		printf("%c\n",*arr);
	}
	_malloc(&arr,n);
	__malloc(&arr,n);
	
	for(i = 0;i < r*n;i++){
		printf("%d \n",*arr);
	}
//	free((char*)arr);
	for(i = 0;i < r;i++){
		for(j = 0;j < n;j++){
			printf("%d\n",arr[i][j]);
		}
	}
	return 0;
}
