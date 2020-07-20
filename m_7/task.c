#include <stdio.h>
#include <unistd.h>

void main()
{
	pid_t id = fork();
//	if(id < 0){
//		printf("fork error!...\n");
//	}else if(id == 0){
//		printf("i am child process!...\n");
//		sleep(100);
//	}

	if( !id){
		sleep(100);
	}
}
