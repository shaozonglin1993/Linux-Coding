/*************************************************************************
    > File Name: sem.h
    > Author: szl
    > Mail: shaozonglin321@163.com
    > Created Time: 2024年03月26日 星期二 14时56分14秒
 ************************************************************************/

#ifndef _SEM_H
#define _SEM_H

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

#endif
