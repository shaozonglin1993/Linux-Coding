#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
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
		printf("fork error!\n");
		return 2;
	}else if(id == 0){
		close(_pipe[0]);
		char* msg = NULL;
		while(1){
			msg = "i am a child!";
			write(_pipe[1],msg,strlen(msg)+1);
			sleep(1);
			printf("%d\n",sizeof(msg));	
			
		}
	}else{
		close(_pipe[1]);
		char _msg[100];
		int j = 0;
   		while(j < 1){
			memset(_msg,'\0',sizeof(_msg));
			printf("%s:code is:%d\n",_msg,ret);
			read(_pipe[0],_msg,sizeof(_msg));
			int a = read(_pipe[0],_msg,sizeof(_msg));
			printf("%d\n",a);
			j++;
		}
		if(waitpid(id,NULL,0) < 0){
			printf("3\n");
			return 3;
		}
	}
	return 0;
}
