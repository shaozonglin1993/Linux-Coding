#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t id;
	int i,fd;
	struct sigaction sa;
	umask(0); //重设置文件权限掩码
	id = fork();//创建子进程用来做守护进程
	if( id < 0){
		printf("fork error!...\n");
		exit(1);
	}else if(id >  0){
		exit(0);//父进程退出
	}

	setsid();//建立新会话
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if(sigaction(SIGCHLD,&sa,NULL) < 0){//注册子进程退出忽略信号
		return;
	}

	if( id = fork() < 0){//再次fork，终止父进程，保持子进程不是会话首进
				  		 //程，从而保证后续不会在和其他终端关联
		printf("fork again  error!...\n");
		return;
	}else if(id > 0){
		exit(0);
	}

	if(chdir("/") < 0){//更改工作目录到根目录
			printf("chdir error!...\n");
			return;
	}
	close(0);
	fd = open("/dev/null",O_RDWR);//关闭标准输入，重定向所有标准（标准输入，输出，错误）
	dup2(fd,1);
	dup2(fd,2);

	return 0;
}
