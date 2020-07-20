#include <stdio.h>
#include <signal.h>

void sig_alrm(int signo)
{
	printf("%d\n",signo);
}

int my_sleep(unsigned int sec)
{
	unsigned int unslept = 0;
	struct sigaction new,old;

	new.sa_handler = sig_alrm;
	sigemptyset(&new.sa_mask);
	new.sa_flags = 0;
	sigaction(SIGALRM,&new,&old);
	
	alarm(sec);
	pause();

	unslept = alarm(0);
	sigaction(SIGALRM,&old,NULL);
	return unslept;

}
int main()
{
	while(1){
		my_sleep(1);
		printf("1 sec passed!\n");
	}
	return 0;
}
