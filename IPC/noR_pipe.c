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
		printf("create pipe error!errno code is:%d\n",errno);
		return 1;
	}
	pid_t id = fork();
	if(id < 0){
		printf("fork error!\n");
		return 2;
	}else if(id == 0){		//子进程
		close(_pipe[0]);
		int i = 0;
		char* msg = NULL;
		while(i < 20){
			if(i < 10){
				msg = "i am a child!";
			//	printf("i am here!\n");
				write(_pipe[1],msg,strlen(msg)+1);
			}
			sleep(1);
			i++;
		}
	}else{			//父进程
			close(_pipe[1]);
			char _msg[100];
			int j = 0;
			while(j<3){
				memset(_msg,'\0',sizeof(_msg));
			//	printf("you here!\n");
				int ret = read(_pipe[0],_msg,sizeof(_msg));
				printf("%s:code is:%d\n",_msg,ret);
				j++;
			}
			close(_pipe[0]);
		//	sleep(10);
			if(waitpid(id,NULL,0)<0){
				return 3;
			}
	}
	return 0;
}
