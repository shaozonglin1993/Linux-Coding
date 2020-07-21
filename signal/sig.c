#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void printfsigset(sigset_t *set)
{
	int i = 0;
	for(;i < 32;i++){
		if(sigismember(set,i)){
			putchar('i');
		}else{
			putchar('0');
		}
	}
//	puts(--);
}

int main()
{
	sigset_t s,p;
	sigemptyset(&s);
	sigaddset(&s,SIGINT);
	sigprocmask(SIG_BLOCK,&s,NULL);
	while(1){
		sigpending(&p);
		printfsigset(&p);
		sleep(1);
	}
	return 0;
}
