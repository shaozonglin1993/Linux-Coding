#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int val = 0;

void* pthread1_run(void* arg)
{
	pthread_mutex_lock(&lock);
	int ret = 0;

	int i = 0;
	for(;i < 5000; i++){
		ret = val;
		printf("val = %d\n",val);
		val = ret + 1;
//		pthread_mutex_unlock(&lock);
	}
		pthread_mutex_unlock(&lock);
}

int main()
{
	pthread_t id1,id2;
	pthread_create(&id1,NULL,pthread1_run,NULL);
	pthread_create(&id2,NULL,pthread1_run,NULL);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	printf("val = %d\n",val);
	return 0;
}
