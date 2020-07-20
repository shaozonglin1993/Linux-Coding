#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

//通过信号机制处理僵尸进程
void sig_child(int sig)
{
	pid_t pid;
	int state;
	//处理僵尸进程
	while((pid = waitpid(-1,&state,WNOHANG)) > 0){
		printf("child %d terminated..\n",pid);
	}
}

int main()
{
	pid_t pid;
	signal(SIGCHLD,sig_child);
	pid = fork();
	if(pid < 0){
		printf("fork error!...\n");
		exit(1);
	}else if(pid == 0){
		printf("i am the child process,pid : %d,i am exitting...\n",getpid());
		exit(0);
	}else{
		printf("i am the father process,i will sleep 2 seconds...\n");
		sleep(2);
		system("ps -o pid,ppid,state,command");
	}
	printf("the father process is exitting...\n");
	return 0;
}
