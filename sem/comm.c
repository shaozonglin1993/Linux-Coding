#include "comm.h"

static int comm_sem_set(int sems,int flags)
{
	key_t _key = ftok(_PROJ_NAME_,_PROJ_ID_);
	if(_key < 0){
		perror("ftok");
		return -1;
	}
	int sem_id = semget(_key,sems,flags);
	if(sem_id < 0){
		perror("semget");
		return -2;
	}
	return sem_id;
}

int create_sem_set(int sems)
{
	int flags = IPC_CREAT|IPC_EXCL|0644;
	return comm_sem_set(0,flags);
}

int get_sem_set()
{
	int flags = IPC_CREAT;
	return comm_sem_set(0,flags);
}

int init_sem_set(int sem_id,int which,int _val)
{
	union semun _un;
	_un.val = _val;

	if(semctl(sem_id,which,SETVAL,_un) < 0){
		perror("semctl");
		return -1;
	}
	return 0;
}

int destroy_sem_set(int sem_id)
{
	if(semctl(sem_id,0,IPC_RMID) < 0){
		perror("semctl");
		return -1;
	}
	return 0;
}

static int op(int sem_id,int which,int op)
{
	struct sembuf _sem;
	_sem.sem_num = which;
	_sem.sem_op = op;
	_sem.sem_flg = 0;

	if(semop(sem_id,&_sem,1) < 0){
		perror("semop");
		return -1;
	}
	return 0;
}

int P(int sem_id, int which)
{
	return op(sem_id, which, -1);
}

int V(int sem_id,int which)
{
	return op(sem_id,which,1);
}
