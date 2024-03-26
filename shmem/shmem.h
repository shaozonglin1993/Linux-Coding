/*************************************************************************
    > File Name: shmem.h
    > Author: szl
    > Mail: shaozonglin321@163.com
    > Created Time: 2024年03月26日 星期二 14时09分26秒
 ************************************************************************/

#ifndef _SHMEM_H
#define _SHMEM_H

//查看共享内存 ipcs -m
//删除指定共享内存段 ipcrm -m shmid

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>

#define _PATH_NAME_ "/tmp"
#define _PROJ_ID_ 0x666


int create_shm(int size);
int get_shm();
int destroy_shm(int shm_id);
void* shm_at(int shm_id);

#endif
