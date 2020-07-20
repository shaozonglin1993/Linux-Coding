#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define NAME_MAX_LEN 64
#define BUF_SIZE 2048

#define FILE_INFO_OK "file info ok"
#define FILE_DATA_OK "file data ok"

typedef struct FILE_INFO_T
{
	char name[NAME_MAX_LEN];
	unsigned int file_len;
}FILE_INFO_T;

void main()
{
	struct sockaddr_in srvaddr, cliaddr;
	socklen_t cliaddr_len;
	int sockfd;
	char buf[BUF_SIZE];
	FILE_INFO_T file_info;
	FILE *fp = NULL;
	int i, len;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&srvaddr, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(8080);
	cliaddr_len = sizeof(cliaddr);

	bind(sockfd, (struct sockaddr*)&srvaddr, sizeof(srvaddr));

	while(1)
	{
		printf("line %d...\n",__LINE__);
		//receive file name
		bzero(&file_info, sizeof(file_info));
		int name_len = 0;
		while(name_len != (NAME_MAX_LEN + 4))
		{
		printf("line %d...\n",__LINE__);
			len = recvfrom(sockfd, &file_info, NAME_MAX_LEN + 4, 0, (struct sockaddr*)&cliaddr, &cliaddr_len);
		printf("line %d...len = %d\n",__LINE__,len);
			if(len < 0)
			{
				printf("ERROR\n");
				return;
			}
			name_len += len;
		}
		printf("recv file: %s, size: %d\n", file_info.name, file_info.file_len);
		//send recv file_name ok
		len = sendto(sockfd, FILE_INFO_OK, sizeof(FILE_INFO_OK), 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
		printf("line %d...len = %d\n",__LINE__,len);
		if(len < 0)
		{
			printf("ERROR\n");
		}
		//create file
		if((fp = fopen(file_info.name, "wb")) == NULL)
		{
			printf("create file %s failed\n", file_info.name);
			return;
		}
		//recv file
		int data_len = 0;
		while(data_len != file_info.file_len)
		{
			len = recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr*)&cliaddr, &cliaddr_len);
			if(len < 0)
			{
				printf("ERROR\n");
				return;
			}
			fwrite(buf, len, 1, fp);
			data_len += len;
		}
		fclose(fp);
		//send recv file ok
		len = sendto(sockfd, FILE_DATA_OK, sizeof(FILE_DATA_OK), 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
		if(len < 0)
		{
			printf("ERROR\n");
		}
	}
	printf("%s\n",buf);
}
