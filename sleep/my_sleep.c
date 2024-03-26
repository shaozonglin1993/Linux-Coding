/*************************************************************************
    > File Name: sleepp.c
    > Author: szl
    > Mail: shaozonglin321@163.com
    > Created Time: 2024年03月26日 星期二 14时18分43秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "my_sleep.h"

void sig_alrm(int signo)
{
	//Do nothing
    printf("hello\n");
}

unsigned int my_sleep(unsigned int msecs)
{
	struct sigaction new,old;
	unsigned int unslept = 0;

	new.sa_handler = sig_alrm;
	sigemptyset(&new.sa_mask);
	new.sa_flags = 0;
	sigaction(SIGALRM,&new,&old);	//注册信号处理函数
	
	alarm(msecs);					//设置闹钟
	pause();
	
	unslept = alarm(0);				//清空闹钟
	sigaction(SIGALRM,&old,NULL);	//恢复默认信号处理动作
	return unslept;
}
