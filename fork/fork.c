/*************************************************************************
    > File Name: fork.c
    > Author: szl
    > Mail: shaozonglin321@163.com
    > Created Time: 2024年03月27日 星期三 16时54分06秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include "fork.h"


int fork_test()
{
	int i = 0;
	for(;i < 2;i++){
		pid_t id = fork();
		if(id == 0){
			printf("child,pid:%d, id = %d\n",getpid(),id);
		}else{
			printf("father,pid:%d, id = %d\n",getpid(),id);
		}
	}

	return 0;
}
