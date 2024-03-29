#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define _MAXLINE_ 80
#define _SERV_PORT_ 8000

int main(int argc,char *argv[])
{
	struct sockaddr_in server_addr;
    //recv buf cache
	char buf[_MAXLINE_];
	int sockfd,n;
    //data ptr to write
	char *str = NULL;

	if(argc != 2){
		fputs("usage: ./client message\n",stderr);
		exit(1);
	}
	str = argv[1];

    //创建socket
	sockfd = socket(AF_INET,SOCK_STREAM,0);

    //连接信息填充
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
	server_addr.sin_port = htons(_SERV_PORT_);

    //connect
	connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
    //write
	write(sockfd, str, strlen(str));
	
    //read
	n = read(sockfd,buf,_MAXLINE_);
	printf("Response from server:\n");

    //向屏幕输出
	write(STDOUT_FILENO, buf, n);

	printf("\n");
	close(sockfd);

	return 0;
}
