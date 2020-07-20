#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	while(1){
		printf("[newshell@host]#");
		//printf("[%s@localhost shell$]",getlogin());
		fflush(stdout);

		char *buff[1024];
		memset(buff,'\0',sizeof(buff));

		ssize_t _sz = read(0, buff, sizeof(buff)-1);
		if(_sz > 0){
			buff[_sz] = '\0';
		}

		char *argv[64];
		char *p = buff;
		int index = 1;
		argv[0] = buff;
		while(*p != '\0'){
			if(*p == ' '){
				*p = '\0';
				p++;
				argv[index++] = p;
			}else{
				p++;
			}
		}
		argv[index] = NULL;
		pid_t pid = fork();
		if(pid == 0){
		//	printf("i am child:%d\n",getpid());
		//	sleep(2);
			char *argv[] = {
				"ls","-l","-i","-a",NULL
			};
			char *env[] = {
				"PATH=hello/i/am/fairy",NULL
			};
			execl("/bin/ls","ls","-l","-a","-i",NULL);
			execv("/bin/ls",argv);
			execle("./hello","ls",NULL,env);
			execlp("ls","ls","-l",NULL);
			execvp(argv[0],argv);
		}else{
		//	printf("i am father:%d\n",getpid());
			pid_t ret = waitpid(pid,NULL,0);
			if(ret > 0){
		//		printf("wait sucess!\n");
			}else{
		//		printf("wait fails!\n");
			}
		}
	}
	return 0;
}









