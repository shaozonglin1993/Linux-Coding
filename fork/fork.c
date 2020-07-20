#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
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
