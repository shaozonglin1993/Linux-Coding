#include"comm.h"
int main()
{
int msg_id = get_msg_queue();
if(msg_id < 0){
printf("%s\n",strerror(errno));
return 1;
}
char buf[_SIZE_];
printf("please enter# ");
fflush(stdout);
while(1){
memset(buf,'\0',sizeof(buf));
ssize_t _s = read(0,buf,sizeof(buf)-1);
if(_s > 0)
	buf[_s-1] = '\0';
printf("+++++++++++++\n");
printf("%s\n",buf);
send_msg(msg_id,buf,client_type);
if(strcasecmp(buf,"quit") ==0 )
	break;
printf("+++++++++++\n");
memset(buf,'\0',sizeof(buf));
recv_msg(msg_id,server_type,buf);
if(strcasecmp(buf,"quit") == 0)
	break;
printf("server# %s\n",buf);
printf("server say done,please enter# ");
fflush(stdout);
}
destroy_msg_queue(msg_id);
return 0;
}
