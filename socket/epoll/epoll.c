#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

void usage(const char *proc)
{
	printf("Usage: %s [ip] [port]\n",proc);
}

void set_nonblock(int fd)
{
	int fl = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, fl|O_NONBLOCK);
}

ssize_t my_read(int fd, char buf[])
{
	int ret = 0;
	int total = 0;
	while((ret = read(fd, buf+total, sizeof(buf)-total)) && errno != EAGAIN){
		total += ret;
	}

	buf[total] = '\0';
	return total;
}

int startup(const char *_ip, int _port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket");
		exit(2);
	}

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(_port);
	local.sin_addr.s_addr = inet_addr(_ip);

	if(bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0){
		perror("bind");
		exit(3);
	}

	if(listen(sock, 5) < 0){
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
	int listen_sock = startup(argv[1], atoi(argv[2]));//read

	int epfd = epoll_create(256);
	if(epfd < 0){
		perror("epoll_create");
		exit(5);
	}
	struct epoll_event _ev;
	_ev.events = EPOLLIN;
	_ev.data.fd = listen_sock;

	epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &_ev);

	struct epoll_event revs[64];
	
	int timeout = -1;
	int num = 0;
	int done = 0;
	while(!done){
		switch((num = epoll_wait(epfd, revs, 64, timeout))){
			case 0:
				printf("timeout\n");
				break;
			case -1:
				perror("epoll_wait");
				break;
			default:
				{
					struct sockaddr_in peer;
					socklen_t len = sizeof(peer);
					int i = 0;
					for(; i < num; i++){
						int rsock = revs[i].data.fd;
						if(rsock == listen_sock && (revs[i].events & EPOLLIN)){
							int new_fd = accept(listen_sock,(struct sockaddr *)&peer, &len);
							if( new_fd > 0){
								printf("get a new client: %s : %d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));

								set_nonblock(new_fd);
								_ev.events = EPOLLIN | EPOLLET;
								_ev.data.fd = new_fd;
								epoll_ctl(epfd, EPOLL_CTL_ADD, new_fd, &_ev);
							}
						}else{
							if(revs[i].events & EPOLLIN){
								char buf[1024];
								//no read!my_read();
								ssize_t _s = read(rsock, buf, sizeof(buf)-1);
								if(_s > 0){
									buf[_s] = '\0';
									printf("client: %s\n",buf);

									_ev.events = EPOLLOUT | EPOLLET;
									_ev.data.fd = rsock;
									epoll_ctl(epfd, EPOLL_CTL_MOD, rsock, &_ev);
								}else if( _s == 0){
									printf("client %d close...\n",rsock);
									epoll_ctl(epfd, EPOLL_CTL_DEL, rsock, NULL);
									close(rsock);
								}else{
									perror("read");
								}
							}else if( revs[i].events & EPOLLOUT ){
								const char *msg = "HTTP/1.0 200 OK\r\n\r\n<html><h1>hello world!+_+|| </h1></html>\r\n";
								//my_write
								write(rsock, msg, strlen(msg));
								epoll_ctl(epfd, EPOLL_CTL_DEL, rsock, NULL);
								close(rsock);
							}else{
							}
						}
					}
				}
				break;
		}
	}
	return 0;
}
