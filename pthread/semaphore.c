#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <semaphore.h>

#define _SEM_PRO_ 10
#define _SEM_CON_ 0

sem_t sem_consume;
sem_t sem_product;

int bank[_SEM_PRO_];

void* consumer(void* arg)
{
	int c = 0;
	while(1){
		sem_wait(&sem_consume);
		int _consume = bank[c];
		printf("consume done...,val is : %d\n",_consume);
		sem_post(&sem_product);
		c = (c+1) % _SEM_PRO_;
		sleep(3);
	}
}

void* producter(void* arg)
{
	int p = 0;
	while(1){
		sem_wait(&sem_product);
		int _product = rand()%100;
		bank[p] = _product;
		printf("product done..., val is: %d\n",_product);
		sem_post(&sem_consume);
		p = (p+1)%_SEM_PRO_;
		sleep(1);
	}
}


void run_product_consume()
{
	pthread_t id_consumer;
	pthread_t id_producter;

	pthread_create(&id_consumer,NULL,consumer,NULL);
	pthread_create(&id_producter,NULL,producter,NULL);

	pthread_join(id_consumer,NULL);
	pthread_join(id_producter,NULL);
}

void destroy_all_sem(int val)
{
	printf("process done...\n");
	sem_destroy( &sem_product );
	sem_destroy( &sem_consume );
	exit(0);
}

void init_all_sem()
{
	signal(2,destroy_all_sem);
	int bank[_SEM_PRO_];
	int _num = sizeof(bank)/sizeof(bank[0]);
	int i = 0;
	for(;i < _num; i++){
		bank[i] = 0;
	}
	sem_init( &sem_product, 0 , _SEM_PRO_);
	sem_init( &sem_consume, 0 , _SEM_CON_);

}

int main()
{
	init_all_sem();
	run_product_consume();

	return 0;
}
