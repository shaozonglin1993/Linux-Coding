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
	char buf[_MAXLINE_];
	char str[INET_ADDRSTRLEN];
	int i,n;

	listenfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(_SER_PORT_);

	bind(listenfd,(struct sockaddr *)&server_addr,sizeof(server_addr));

	listen(listenfd,20);

	printf("Accepting connectionos ...\n");
	while(1){
		cliaddr_len = sizeof(client_addr);
		connfd = accept(listenfd,(struct sockaddr *)&client_addr,&cliaddr_len);

		n = read(connfd,buf,_MAXLINE_);
		printf("received from %s at PORT %d\n",inet_ntop(AF_INET,&client_addr.sin_addr,str,sizeof(str)),ntohs(client_addr.sin_port));

		for(i = 0; i < n; i++){
			buf[i] = toupper(buf[i]);
		}
		write(connfd,buf,n);
		close(connfd);
	}
}
