#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <dirent.h>
#include <sys/stat.h>

#define _PATH_MAX_LEN_ 128
#define _MAXLINE_ 80
#define _BUF_SIZE_ 50
#define _SERV_PORT_  8000

#define FILE_INFO_OK "file info ok"
#define FILE_DATA_OK "file data ok"

//file info
typedef struct FILE_INFO_T
{
	char path[_PATH_MAX_LEN_];
	char type;		//0 -> folder  1 -> file
	unsigned int file_len;
}FILE_INFO_T;

int sock_init(char *addr, struct sockaddr_in *servaddr, struct sockaddr_in *cliaddr)
{
	int sockfd;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	(*servaddr).sin_family = AF_INET;
	//inet_pton(AF_INET, addr, &servaddr.sin_addr);
	(*servaddr).sin_addr.s_addr = inet_addr(addr);
	(*servaddr).sin_port = htons(_SERV_PORT_);

	return sockfd;
}

//process dir
void dirprocess(char *dir, int sockfd, struct sockaddr_in servaddr, struct sockaddr_in cliaddr)
{
	DIR *dp = NULL;
	FILE *fp = NULL;
	struct dirent *entry;
	struct stat statbuf;
	FILE_INFO_T file_info;
	char buf[_BUF_SIZE_];
	memcpy(file_info.path, dir, strlen(dir)+1);

	socklen_t cli_len = sizeof(cliaddr);

	if((dp = opendir(dir)) == NULL)
	{
		fprintf(stderr,"canot open dir %s...\n", dir);
		return;
	}
	int len = 0;
	chdir(dir);
	while((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name, &statbuf);
		if(S_IFDIR & statbuf.st_mode)
		{
			file_info.type = 0;
			//find a dir
			if((strcmp(".", entry->d_name) == 0) || (strcmp("..", entry->d_name) == 0))
			{
				continue;
			}
			//send folder
			len = sendto(sockfd, &file_info, sizeof(file_info), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
			
			if(len < 0)
			{
				printf("send file info error...\n");
				return;
			}
			int rev_len = 0;
			//wait for file info rev OK
			while(rev_len != sizeof(FILE_INFO_OK))
			{
				len = recvfrom(sockfd, buf, sizeof(FILE_INFO_OK), 0, (struct sockaddr*)&cliaddr, &cli_len);
				rev_len += len;
			}
			if(memcmp(FILE_INFO_OK, buf, sizeof(FILE_INFO_OK)) != 0)
			{
				printf("rev FILE_INFO_OK error...\n");
			}
			//recurse
			dirprocess(entry->d_name, sockfd, servaddr, cliaddr);
		}
		else if(S_IFREG & statbuf.st_mode)
		{
			file_info.type = 1;
			//send file
			fseek(fp, 0L, SEEK_SET);
			int data_len = 0;
			while(data_len != file_info.file_len)
			{
				int read_len = fread(buf, 1, _BUF_SIZE_, fp);
				len = sendto(sockfd, buf, read_len, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
				if(len < 0)
				{
					printf("send file data error...\n");
					return;
				}
				data_len += len;
			}
			data_len = 0;
			while(data_len != sizeof(FILE_DATA_OK))
			{
				len = recvfrom(sockfd, buf, sizeof(FILE_INFO_OK), 0, (struct sockaddr*)&servaddr, &cli_len);
				data_len += len;
			}
			if(memcmp(FILE_DATA_OK, buf, sizeof(FILE_INFO_OK)) != 0)
			{
				printf("rev FILE_DATA_OK error...\n");
			}
		}
		else
		{
			//neither dir nor file
		}
		fclose(fp);
	}
}

int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr, cliaddr;
	if(argc < 3)
	{
		printf("please input server ip and file name...\n");
		return -1;
	}

	char *topdir = ".";
	char *ipaddr = argv[1];

	int sockfd = sock_init(ipaddr, &servaddr, &cliaddr);
	topdir = argv[2];
	dirprocess(topdir, sockfd, servaddr, cliaddr);


	close(sockfd);

	return 0;
}
