#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
	int _pipe[2];
	int ret = pipe(_pipe);
	if(ret == -1){
		printf("create pipe error!error code is:%d\n",errno);
		return 1;
	}
	pid_t id = fork();
	if(id < 0){
		printf("fork error1\n");
		return 2;
	}else if(id == 0){
		close(_pipe[0]);
		int i = 0;
		char* msg = NULL;
		while(i < 20){
			if(i < 10){
				msg = "i am a child!";
				write(_pipe[1],msg,strlen(msg)+1);
			}
			sleep(1);
			i++;
		}
		close(_pipe[1]);
	}else{
		char _msg[100];
		int j = 0;
		while(j<20){
			memset(_msg,'\0',sizeof(_msg));
			int ret = read(_pipe[0],_msg,sizeof(_msg));
			printf("%s:code is:%d\n",_msg,ret);
			j++;
		}
		if(waitpid(id,NULL,0)<0){
			return 3;
		}
	}
	return 0;
}
