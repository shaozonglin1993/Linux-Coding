#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main()
{
	int _pipe[2];		
	int ret = pipe(_pipe);
	if(ret == -1){
		printf("create pipe error!error code is : %d\n",errno);
		return 1;
	}
	pid_t id = fork();
	if(id < 0){
		printf("fork error!");
		return 2;
	}else if(id == 0){		//子进程
		close(_pipe[0]);	//关闭读端
		int i = 0;
		char* msg = "I am a child!";
		while(i < 5){
			write(_pipe[1], msg,strlen(msg)+1);
			sleep(1);
			i++;
		}
	}else{					//父进程
			close(_pipe[1]);//关闭写端
			char _msg[100];
			int j = 0;
			while(j < 10){
				printf("000\n");
				memset(_msg,'\0',sizeof(_msg));
				read(_pipe[0],_msg,sizeof(_msg));
				printf("%s\n",_msg);
				j++;
			}
		}
	return 0;
}
