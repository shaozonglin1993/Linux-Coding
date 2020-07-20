#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(pid < 0){
		printf("fork error!...\n");
		exit(1);
	}else if(pid == 0){
		printf("i  am the child process!...\n");
		printf("child process pid : %d\tppid : %d\n",getpid(),getppid());

		sleep(5);

		printf("child process pid : %d\tppid : %d\n",getpid(),getppid());
		printf("child process exit...\n");
	}else{
		printf("i am the father process!...\n");
		sleep(1);
		printf("father process is exited...\n");
	}
	return 0;
}
