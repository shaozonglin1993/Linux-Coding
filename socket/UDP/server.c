#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define _MAXLINE_ 80
#define _SERV_PORT_  8000

int main()
{
	struct sockaddr_in server_addr,client_addr;
	socklen_t cliaddr_len;
	int sockfd;
	char buf[_MAXLINE_];
	char str[INET_ADDRSTRLEN];
	int i, n;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0){
		printf("create socket error!...\n");
		return -1;
	}

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(_SERV_PORT_);

	if(bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0){
		printf("bind error!...");
		close(sockfd);
		return 1;
	}

	printf("Accepting connections ...\n");
	while(1){
		cliaddr_len = sizeof(client_addr);
		//n = recvfrom(sockfd, buf, _MAXLINE_, 0,(struct sockaddr *)&client_addr, &cliaddr_len);
		n = recvfrom(sockfd, buf, _MAXLINE_, 0,(struct sockaddr *)&client_addr, &cliaddr_len);
		if(n == -1){
			printf("recvfrom error...\n");
			exit(1);
		}
		printf("received from %s at PORT %d\n",inet_ntop(AF_INET, &client_addr.sin_addr, str,sizeof(str)),ntohs(client_addr.sin_port));

		for(i = 0; i < n; i++){
			buf[i] = toupper(buf[i]);
		}
		n = sendto(sockfd, buf, n, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
		if(n == -1){
			printf("sendto error...\n");
		}
	}
	return 0;
}
