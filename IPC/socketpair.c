#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

int main()
{
	int fd[2];
	int ret = socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);
	if(ret != 0){
		perror("socketpair()");
		return ret;
	}

	pid_t id = fork();
	if( id < 0){
		perror("fork()");
		return id;
	}else if(id == 0){//child
		close(fd[0]);//close read
		char buf[1024];
		while(1){
			memset(buf, 0, sizeof(buf));
			strcpy(buf, "child: hello world!");
			write(fd[1], buf, sizeof(buf));
			read(fd[1], buf, sizeof(buf));
			sleep(1);
			printf("child :%s\n",buf);
		}
	}else if(id > 0){//father
		close(fd[1]);//close write
		char buf[1024];
		while(1){
			memset(buf, 0, sizeof(buf));
			read(fd[0], buf, sizeof(buf));
			printf("father: %s\n",buf);
			strcpy(buf, "father: hello child!");
			write(fd[0], buf, sizeof(buf));
		}
	}else{}

	return 0;
}
