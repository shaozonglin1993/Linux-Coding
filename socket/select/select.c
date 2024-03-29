#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>

int fds[128];
const int len = 128;

static void usage(const char* proc)
{
	printf("Usage: %s [ip] [port]\n",proc);
}

int startup(const char *_ip, int _port)
{
    //create socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if( sock < 0){
		perror("socket");
		exit(2);
	}

	int opt = 1;
    //set reuse
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(_port);
	local.sin_addr.s_addr = inet_addr(_ip);

    //bind
	if( bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0){
		perror("bind");
		exit(3);
	}

    //listen
	if( listen(sock, 5) < 0){
		perror("listen");
		exit(4);
	}

	return sock;
}

int main(int argc, char *argv[])
{
	if(argc != 3){
		usage(argv[0]);
		exit(1);
	}

	int i = 0;
	for(; i < len; i++){
		fds[i] = -1;
	}

    //address cache
	char str[INET_ADDRSTRLEN];
    
	int listen_sock = startup(argv[1], atoi(argv[2]));

	fd_set rfds;//read fd set;
	fds[0] = listen_sock;
	
	int done = 0;
	while(!done){
		int max_fd = -1;
		FD_ZERO(&rfds);
		for(i = 0; i < len; i++){
			if( fds[i] != -1){
				FD_SET(fds[i], &rfds);
			}
			max_fd = fds[i] > max_fd?fds[i]:max_fd;
		}
		struct timeval timeout = {5, 0};
		switch(select(max_fd+1, &rfds, NULL, NULL, NULL)){
			case 0:
				printf("timeout\n");
				break;
			case -1:
				perror("select");
				break;
			default:
				{
					if( FD_ISSET(listen_sock, &rfds) ){
						struct sockaddr_in peer;
						socklen_t len = sizeof(peer);
						int new_fd = accept(listen_sock, (struct sockaddr *)&peer, &len);
						if(new_fd > 0){

                            inet_ntop(AF_INET, peer.sin_addr, str, sizeof(str));

							printf("get a new client-> %s:%d\n", str, ntohs(peer.sin_port));
							for(i = 0; i < len; i++){
								if(fds[i] == -1){
									fds[i] = new_fd;
									break;
								}
							}
							if( i == len){
								close(new_fd);
							}
						}
					}else{
						char buf[1024];
						for( i = 0; i < len; i++){
							if( i != -1 && FD_ISSET(fds[i], &rfds) ){
								ssize_t _s = read(fds[i], buf, sizeof(buf));
								if(_s > 0){
									buf[_s] = '\0';
									printf("client %d is closed...\n", fds[i]);
									close(fds[i]);
									fds[i] = -1;
								}else{
									perror("read");
								}
							}
						}

					}
						
				}
				break;
		}
	}
	return 0;
}
