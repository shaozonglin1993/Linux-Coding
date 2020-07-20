#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SER_IP INADDR_ANY
#define PORT 8080

#define NAME_MAX_LEN 64
#define BUF_SIZE 2048

#define FILE_INFO_OK "file info ok"
#define FILE_DATA_OK "file data ok"

#define FILE_NAME "udpclient.c"

typedef struct FILE_INFO_T
{
	char name[NAME_MAX_LEN];
	unsigned int file_len;
}FILE_INFO_T;

int main(int argc, char* argv[])
{
	struct sockaddr_in srvaddr, cliaddr;
	socklen_t cliaddr_len;
	int sockfd;
	FILE_INFO_T file_info;
	FILE *fp = NULL;
	int len = 0;
	char buf[BUF_SIZE];

	if(argc < 3)
	{
		printf("please input server ip and file name\n");
		return 0;
	}

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&srvaddr, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr(argv[1]);
	srvaddr.sin_port = htons(PORT);

	cliaddr_len = sizeof(cliaddr);
	bzero(&file_info, sizeof(file_info));

	char *p = argv[2];
	char *name = argv[2];

	while(p < argv[2] + strlen(argv[2]))
	{
		if(*p == '\\' || *p == '/')
		{
			name = p + 1;
		}
		p++;
	}

	printf("file name: %s\n",name);
	memcpy(file_info.name, name, strlen(name) + 1);

	//get file size
	if((fp = fopen(argv[2], "rb")) == NULL)
	{
		printf("create file %s failed\n",file_info.name);
		return 0;
	}

	printf("line %d...\n",__LINE__);

	fseek(fp, 0L, SEEK_END);
	file_info.file_len = ftell(fp);

	printf("line %d...\n",__LINE__);

	//send file info
	int info_len = 0;
	len = sendto(sockfd, &file_info, sizeof(file_info), 0, (struct sockaddr*)&srvaddr, sizeof(srvaddr));
	
	
	printf("line %d...len = %d\n",__LINE__,len);

	if(len < 0)
	{
		printf("ERROR\n");
	}

	//wait file info ok
	while(info_len != sizeof(FILE_INFO_OK))
	{
		len = recvfrom(sockfd, buf, sizeof(FILE_INFO_OK), 0, (struct sockaddr*)&srvaddr, &cliaddr_len);
		info_len += len;
	printf("line %d...len = %d\n",__LINE__,info_len);
	}

	if(memcmp(FILE_INFO_OK, buf, sizeof(FILE_INFO_OK)) != 0)
	{
		printf("wait file info error\n");
		return 0;
	}

	//send file data
	fseek(fp, 0L, SEEK_SET);
	int data_len = 0;
	while(data_len != file_info.file_len)
	{
		int read_len = fread(buf, 1, BUF_SIZE, fp);
		len = sendto(sockfd, buf, read_len, 0, (struct sockaddr*)&srvaddr, sizeof(srvaddr));
	printf("line %d...len = %d\n",__LINE__,len);
		if(len < 0)
		{
			printf("ERROR\n");
			return 0;
		}
		data_len += len;
	}

	data_len = 0;
	while(data_len != sizeof(FILE_DATA_OK))
	{
		len = recvfrom(sockfd, buf, sizeof(FILE_INFO_OK), 0, (struct sockaddr*)&srvaddr, &cliaddr_len);
	printf("line %d...len = %d\n",__LINE__,len);
		data_len += len;
	}
	if(memcmp(FILE_DATA_OK, buf, sizeof(FILE_DATA_OK)) != 0)
	{
		printf("wait file info error\n");
		return 0;
	}
	fclose(fp);
	printf("send file ok\n");
	
	return 1;
}
