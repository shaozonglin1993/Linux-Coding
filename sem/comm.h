#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <string.h>
#include <sys/sem.h>
#include <unistd.h>

#define _PROJ_NAME_ "/tmp"
#define _PROJ_ID_ 0x6666

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
};

int create_sem_set(int sems);
int get_sem_set();
int init_sem_set(int sem_id,int which,int _val);
int destroy_sem_set(int sem_id);
int P(int sem_id,int which);
int V(int sem_id,int which);
