#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


void* pthread_run1(void* _val)
{
	printf("pthread 1 is returning...\n");
	return (void*)1;		//return 返回
}

void* pthread_run2(void* _val)
{
	printf("pthread 2 is exiting...\n");
	pthread_exit((void*)2);		//pthread_exit 退出
}

void* pthread_run3(void* _val)
{
	while(1){
		printf("pthread 3 is running,waitting tobe canceled...\n");
		sleep(1);				//被其他进程canceld
	}
	return NULL;
}


int main()
{
	void* ret;
	pthread_t id1, id2, id3;
	
	//进程return((void*)1);
	pthread_create(&id1, NULL, pthread_run1, NULL);
	pthread_join(id1,&ret);
	printf("pthread 1 return,pthread id is : %u, reutrn code is : %d\n",(unsigned long)id1,(int)ret);

	//进程pthread_exit((void*)2);
	pthread_create(&id2, NULL, pthread_run2, NULL);
	pthread_join(id2,&ret);
	printf("pthread 2 return,pthread id is : %u, reutrn code is : %d\n",(unsigned long)id2,(int)ret);
	
	//进程canceld,return NULL;
	pthread_create(&id3, NULL, pthread_run3, NULL);
	sleep(3);
	pthread_cancel(id3);
	pthread_join(id3,&ret);
	printf("pthread 3 return,pthread id is : %u, reutrn code is : %d\n",(unsigned long)id3,(int)ret);
	
	return 0;
}





