#pragma once

#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>

#define _SIZE_ 1024
#define PATH_NAME "."
#define PROJ_ID 0x0666

struct msgbuf{
long mtype;
char mtext[_SIZE_]
};

extern int client_type;
extern int server_type;
int create_msg_queue();
int get_msg_queue();
int send_msg(int msg_id,const char *msg,int send_type);
int recv_msg(int msg_id,int recv_type,char *msg_out);
int destroy_msg_queue(int msg_id);
