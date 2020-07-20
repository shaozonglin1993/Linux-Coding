#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


int main()
{
	int fd = open("./log", O_CREAT | O_RDWR, 0644);
	if( fd < 0){
		perror("open()");
		return fd;
	}

	close(1);
	int new_fd = dup2(fd,1);

	char buf[1024];
	while(1){
		memset(buf, '\0', sizeof(buf));
		fgets(buf, sizeof(buf), stdin);
		if( strncmp("quit", buf, 4) == 0 ){
			break;
		}
		printf("%s", buf);
		fflush(stdout);
	}
	close(new_fd);
	return 0;
}
