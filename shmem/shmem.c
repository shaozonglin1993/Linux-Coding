/*************************************************************************
    > File Name: shmem.c
    > Author: szl
    > Mail: shaozonglin321@163.com
    > Created Time: 2024年03月26日 星期二 14时12分25秒
 ************************************************************************/

#include"shmem.h"

//
static int comm(int flag, int size)
{
    //把一个已存在的路径名和一个整数标识符转换成IPC键值
    key_t _key = ftok(_PATH_NAME_, _PROJ_ID_);
    if(_key < 0){
        printf("comm:%s\n",strerror(errno));
        return -1;
    }
   //如果共享内存不存在，创建共享内存，
   //如果存在就打开共享内存
    int shm_id = shmget(_key, size, flag);

    if(shm_id < 0){
        printf("shmget:%s\n", strerror(errno));
        return -1;
    }

    return shm_id;
}

int create_shm(int size)
{
    //访问权限
    int flag = IPC_CREAT | 0666;

    return comm(flag, size);
}

int get_shm()
{
    int flag = IPC_CREAT;

    return comm(flag, 0);
}

int destroy_shm(int shm_id)
{
    //对共享内存执行相关操作，这里删除共享内存
    if(shmctl(shm_id, IPC_RMID, NULL) < 0){
        printf("%s\n",strerror(errno));
        return -1;
    }
    return 0;
}

void *shm_at(int shm_id)
{
    //将共享内存链接进程地址空间
    return shmat(shm_id, NULL, 0);
}

int shm_dt(void *shm_addr)
{
    //将共享内存与当前连接进程脱离
    return shmdt(shm_addr);
}

