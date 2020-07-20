#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(pid < 0){
		printf("fork error!...\n");
		exit(1);
	}else if(pid == 0){
		printf("i am the child process,i am exitting...\n");
		exit(0);
	}
	printf("i am the father process,i will sleep 2 seconds...\n");
	sleep(2);
	system("ps -o pid,ppid,state,tty,command");
	printf("father process is exitting...\n");
	system("ps -o pid,ppid,state,tty,command");
	return 0;
}
