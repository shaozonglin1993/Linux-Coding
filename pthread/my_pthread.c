#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t id;
void *pthread_run(void* _val)
{
	printf("%s :pid is :%d,tid is :%u\n",(char*)_val,(int)getpid(),(unsigned long long)pthread_self() );
	return NULL;
}

int main()
{
	int ret = pthread_create(&id, NULL, pthread_run, NULL);
	if(ret != 0){
		printf("create pthread error! info is : %s\n",strerror(ret));
		exit(ret);
	}
	printf("main pthread run : pid is :%d,tid is : %u\n",(int)getpid(),(unsigned long long)pthread_self());
	printf("ret : %d\n",ret);
	sleep(20);
	return 0;
}
