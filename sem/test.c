/*************************************************************************
  > File Name: test.c
  > Author: szl
  > Mail: shaozonglin321@163.com
  > Created Time: 2024年03月26日 星期二 14时57分53秒
 ************************************************************************/


#include <stdio.h>
#include <sys/types.h>
#include "sem.h"

int main()
{
    int sem_id = create_sem_set(1);
    init_sem_set(sem_id,0,1);

    pid_t id = fork();
    if(id == 0){
        int c_sem_id = get_sem_set();
        while(1){
            P(c_sem_id,0);
            printf("A");
            fflush(stdout);
            sleep(1);
            printf("A");
            fflush(stdout);
            sleep(1);

            V(c_sem_id,0);
        }
    }else{
        while(1){
            P(sem_id,0);
            printf("C");
            fflush(stdout);
            sleep(2);
            printf("C");
            fflush(stdout);
            sleep(2);
            V(sem_id,0);
        }
        wait(NULL);
        destroy_sem_set(sem_id);
    }
    return 0;
}
