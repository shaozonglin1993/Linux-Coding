#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define _MAXLINE_ 80
#define _SER_PORT_ 8000

int main()
{
	struct sockaddr_in server_addr,client_addr;
	socklen_t cliaddr_len;
	int listenfd,connfd;
    //recv data buf
	char buf[_MAXLINE_];
    //address cache
	char str[INET_ADDRSTRLEN];
	int i,n;

    //create socket
	listenfd = socket(AF_INET,SOCK_STREAM,0);

    //初始化填充通信参数
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(_SER_PORT_);

    //bind
	bind(listenfd,(struct sockaddr *)&server_addr,sizeof(server_addr));

    //listen
	listen(listenfd,20);

	printf("Accepting connectionos ...\n");
	while(1){
		cliaddr_len = sizeof(client_addr);

        //accept
		connfd = accept(listenfd,(struct sockaddr *)&client_addr,&cliaddr_len);

        //read
		n = read(connfd,buf,_MAXLINE_);

        inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str));

		printf("received from %s at PORT %d\n", str, ntohs(client_addr.sin_port));

		for(i = 0; i < n; i++){
			buf[i] = toupper(buf[i]);
		}
        //write
		write(connfd,buf,n);
		close(connfd);
	}
    
    return 0;
}
