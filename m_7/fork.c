#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

//int main()
//{
/*
	pid_t pid = getpid();

	pid_t id = fork();
	if(-1 == id){
		printf("fork error!return code is:%d\n",errno);
		return 2;
	}else if(0 == id){
		printf("child pid is: %d\n",getpid());
		exit(3);
	}else{
		printf("father pid is:%d,return pid is:%d\n",getpid(),id);
		sleep(10);
	}
	return 0;
}
*/
	int glob = 6;
	char buf[] = "a write to stdout!\n";
	
	int main()
	{
		pid_t pid;
		int var = 88;
		if(write(STDOUT_FILENO,buf,sizeof(buf)-1)!=sizeof(buf)-1){
			perror("write error!");
			printf("before fork\n");
		}

//		pid_t pid = fork();
		if((pid = fork()) < 0){
			perror("fork error");
		}else if(pid == 0){
			glob++;
			var++;
		}else{
			sleep(2);
		}

		printf("pid = %d,glob = %d,var = %d\n",getpid(),glob,var);
		exit(0);
	}

