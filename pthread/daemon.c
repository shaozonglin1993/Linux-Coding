#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define _MAXFILE_ 65535

int main()
{
	pid_t id;
	int i,fd,len;
	char *buf = "i am a daemon!...\n";
	len = strlen(buf);
//	struct sigaction sa;
//	umask(0); //重设置文件权限掩码
	id = fork();//创建子进程用来做守护进程
	if( id < 0){
		printf("fork error!...\n");
		exit(1);
	}else if(id >  0){//父进程
		exit(0);
	}

	setsid();//建立新会话
//	sa.sa_handler = SIG_IGN;
//	sigemptyset(&sa.sa_mask);
//	sa.sa_flags = 0;

	chdir("/");
	umask(0);
	for(i=0;i<_MAXFILE_;i++){
		close(i);
	}
	while(1){
		if(fd = open("/tmp/daemon",O_CREAT|O_WRONLY|O_APPEND,0600) < 0){
			printf("open file error!...\n");
			exit(0);
		}
		write(fd,buf,len+1);
		close(fd);
		sleep(5);
	}
//	if(sigaction(SIGCHLD,&sa,NULL) < 0){//注册子进程退出忽略信号
//		return;
//	}

//	if( id = fork() < 0){
//		printf("fork error!...\n");
//		return;
//	}else if(id > 0){
//		exit(0);
//	}
//
//	if(chdir("/") < 0){
//			printf("chdir error!...\n");
//			return;
//	}
//	close(0);
//	fd = open("/pthread/log",O_RDWR);
//	dup2(fd,1);
//	dup2(fd,2);
//	//使子进程独立,摆脱原会话机制；摆脱远近成组的控制；摆脱控制终端的控制
//	if( chdir("/") < 0 ){//改变当前工作目录，也使为了摆脱父进程的影响
//		printf("chdir error1...\n");
//		return -1;
//	}

	return 0;
}
