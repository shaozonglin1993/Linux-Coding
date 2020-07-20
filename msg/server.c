#include"comm.h"
int main()
{
int msg_id = create_msg_queue();
if(msg_id < 0){
printf(" server.c:%s\n",strerror(errno));
return 1;
}
char buf[_SIZE_];
while(1){
memset(buf,'\0',sizeof(buf));
recv_msg(msg_id,client_type,buf);
if(strcasecmp(buf,"quit") == 0)
	break;
printf("client# %s\n",buf);
printf("client say done,please enter# ");
fflush(stdout);
memset(buf,'\0',sizeof(buf));
ssize_t _s = read(0,buf,sizeof(buf)-1);
if(_s > 0)
	buf[_s-1] = '\0';
send_msg(msg_id,buf,server_type);
}
destroy_msg_queue(msg_id);
return 0;
}
