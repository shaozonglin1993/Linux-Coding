#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(pid < 0){
		printf("fork 1  error\n");
		exit(1);
	}else if(pid == 0){
		printf("i am the first child process.pid : %d\tppid : %d\n",getpid(),getppid());
		pid = fork();
		if(pid < 0){
			printf("fork 2  error\n");
			exit(1);
		}else if(pid > 0){
		printf("first process is exited.\n");		
		exit(0);
		}
		sleep(3);
		printf("i am the second child process.pid :%d\tppid : %d\n",getpid(),getppid());
		exit(0);
	}
	if(waitpid(pid,NULL,0) != pid){
		perror("waitepid error.");
		exit(1);
	}
	exit(0);


	return 0;
}
