#include <stdio.h>
#include <pthread.h>

void* pthread_run(void* arg)
{
//	pthread_detach(pthread_self());
	printf("%s\n",(char*)arg);
	return NULL;
}


int main()
{
	pthread_t id;
	int ret = pthread_create(&id,NULL,pthread_run,"pthread is running...");
	if(ret != 0){
		printf("create thread error! info is : %s\n",strerror(ret));
		return ret;
	}
	//wait
	int tret = 0;
	sleep(1);
//	if( 0 == pthread_join(id,NULL)){
	if(1){
	printf("pthread wait sucess!\n");
		tret = 0;
		printf(" %d\n",tret);
	}else{
	printf("pthread wait failed!\n");
		tret = 1;
		printf(" %d\n",tret);
	}
	int a =	pthread_detach(id);
//	tret = pthread_join(id,NULL);
//	printf("tret : %d\n",tret);
	printf("a : %d\n",a);
	return tret;
}
