#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define _PATH_ "./log"

int main()
{
	uid_t uid;
	uid_t euid;
	pid_t pid;
	pid_t ppid;
	gid_t gid;
	gid_t egid;
	pid = fork();
	if(pid < 0){
		printf("fork error %d\n",errno);
		exit(2);
	}else if(pid == 0){
		uid = getuid();
		euid = geteuid();
		printf("child-> pid:%d\nppid :%d\nuid:%d\neuid:%d\ngid:%d\negid:%d\n",getpid(),getppid(),uid,euid,getgid(),getegid());
	}else{
		uid = getuid();
		euid = geteuid();
		printf("father->pid:%d\nppid:%d\nuid:%d\neuid:%d\ngid:%d\negid:%d\n",getpid(),getppid(),uid,euid,getgid(),getegid());
		printf("\n");
		sleep(2);
	}

	FILE *fp = fopen(_PATH_,"w");
	if(NULL == fp){
		printf("%s open file %s error,error code is:%d\n",__FUNCTION__,_PATH_,errno);
		return 1;
	}
	char* str = "this is a test\n";
	int i = 0;
	while(i < 100){
		fwrite(str,1,strlen(str),fp);
		i++;
	}
	close(fp);

	return 0;
}
