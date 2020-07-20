#include<stdio.h>
#include<stdlib.h>

int main()
{
	int r,n;
	scanf("%d%d",&r,&n);
	int size = r*n;
	int **p=NULL;
	int *arr=(int*)malloc(sizeof(int));
	if(NULL==arr){
		perror("malloc error");
		exit(1);
	}
	*p = arr;
	int i = 0, j = 0;
	for(;i < r;i++){
		for(;j < n;j++){
			arr[i][j];
		}
	}
}
