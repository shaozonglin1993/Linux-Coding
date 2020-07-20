#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define _READER_NUM_ 3
#define _WRITE_NUM_  2

pthread_rwlock_t lock;
int buf = 0;

void* read(void* arg)
{
	int i = 0;
	pthread_detach(pthread_self());
	while(1){
	//	if(pthread_rwlock_tryrdlock(&lock) != 0){
		if(pthread_rwlock_rdlock(&lock) != 0){
		printf("writer is writing, reader waiting...\n");
		}else{
			printf("reader is : %u , read val is: %d\n",pthread_self(),buf);
			pthread_rwlock_unlock(&lock);
		}
		sleep(1);
	}
}

void* write(void* arg)
{
	int i = 0;
	pthread_detach(pthread_self());
	while(1){
	//	if(pthread_rwlock_trywrlock(&lock) != 0){
		if(pthread_rwlock_wrlock(&lock) != 0){
			printf("reader is reading, writer waiting...\n");
			sleep(1);
		}else{
			buf++;
			printf("writer is : %u , write val is: %d\n",pthread_self(),buf);
			pthread_rwlock_unlock(&lock);
			sleep(1);
		}
	}
}

int main()
{
	pthread_rwlock_init(&lock,NULL);

	pthread_t id;
	int i = 0;

	for( i=0; i < _WRITE_NUM_; i++){
		pthread_create(&id,NULL,write,NULL);
	}

	for( i=0; i < _READER_NUM_; i++){
		pthread_create(&id,NULL,read,NULL);
	}

	sleep(100);

	return 0;
}
