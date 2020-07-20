#include"comm.h"
int client_type = 1;
int server_type = 2;
int comm(int flag)
{
key_t _key = ftok(PATH_NAME,PROJ_ID);
if(_key < 0){
printf("comm.c:comm %s\n",strerror(errno));
return -1;
}
int msg_id = msgget(_key,flag);
return msg_id;
}
int create_msg_queue()
{
int flag = IPC_CREAT;
return comm(flag);
}
int get_msg_queue()
{
int flag = IPC_CREAT;
return comm(flag);
}
int send_msg(int msg_id,const char *msg,int send_type)
{
printf("1\n");
struct msgbuf _buf;
memset(_buf.mtext,'\0',sizeof(_buf.mtext));
printf("2\n");
_buf.mtype = send_type;
printf("3\n");
printf("%s\n",msg);
strncpy(_buf.mtext,msg,strlen(msg)+1);
printf("4\n");
if(msgsnd(msg_id,&_buf,sizeof(_buf.mtext),0) < 0){
printf("comm:send_msg %s\n",strerror(errno));
return -1;
}
return 0;
}
int recv_msg(int msg_id,int recv_type,char *msg_out)
{
struct msgbuf _buf;
_buf.mtype = 0;
memset(_buf.mtext,'\0',sizeof(_buf.mtext));
if(msgrcv(msg_id,&_buf,sizeof(_buf.mtext),recv_type,0) < 0){
printf("comm.c:recv_mag %s\n",strerror(errno));
return -1;
}
else
{
strncpy(msg_out,_buf.mtext,sizeof(_buf));
return 0;
}
}
int destroy_msg_queue(int msg_id)
{
if(msgctl(msg_id,IPC_RMID,NULL) != 0){
printf("comm.c:destroy_msg %s\n",strerror(errno));
return -1;
}
return 0;
}
