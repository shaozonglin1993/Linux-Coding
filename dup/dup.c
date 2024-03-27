/*************************************************************************
  > File Name: dup.c
  > Author: szl
  > Mail: shaozonglin321@163.com
  > Created Time: 2024年03月27日 星期三 16时22分51秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "dup.h"

int dup_test()
{
    int fd = open("./log", O_CREAT | O_RDWR, 0644);
    if(fd < 0){
        perror("open()");
        return fd;
    }

    close(1);
    int new_fd = dup(fd);
    if(new_fd == -1){
        perror("dup()");
        return -1;
    }

    close(fd);
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


int dup2_test()
{
    int fd = open("./log", O_CREAT | O_RDWR, 0644);
    if( fd < 0 ){
        perror("open()");
        return fd;
    }

    close(1);
    int new_fd = dup2(fd,1);

    char buf[1024];
    while(1){
        memset(buf, '\0', sizeof(buf));
        fgets(buf, sizeof(buf), stdin);
        if( strncmp("quit", buf, 4) == 0  ){
            break;
        }

        printf("%s", buf);
        fflush(stdout);
    }

    close(new_fd);
    return 0;
}

