#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define _MAXLINE_ 80
#define _SERV_PORT_  8000

int main(int argc, int* argv[])
{
	struct sockaddr_in servaddr;
	int sockfd, n;
    
    //recv buf cache
	char buf[_MAXLINE_];
	char str[INET_ADDRSTRLEN];
	socklen_t servaddr_len;

    //create socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(_SERV_PORT_);

    //read input
	while(fgets(buf, _MAXLINE_, stdin)!= NULL){
        //send to
		n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)\
				&servaddr, sizeof(servaddr));
		if(n == -1){
			printf("sendto error\n");
		}
        //recvfrom
		n = recvfrom(sockfd, buf, _MAXLINE_, 0, NULL, 0);
		if(n == -1){
			printf("recvfrom error\n");
		}
		write(STDOUT_FILENO, buf, n);
	}

	close(sockfd);
	return 0;
}
