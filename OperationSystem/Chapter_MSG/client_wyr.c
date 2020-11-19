#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>

typedef struct
{
    int ball;
    unsigned long limit;
    _Atomic int cmd;

} ping_pong_mem_t;


int main(int argc,char **argv)
{


    char *tmp;
    unsigned long limit;

    key_t key=ftok("/root/Program",'u');
    int id;
    id= shmget(key,sizeof(ping_pong_mem_t),0);

    if(id<0)
    {
        perror("shmget");
        return 1;
    }

    ping_pong_mem_t *mem;

    mem = shmat(id,NULL,0);
    if(mem==(void*)-1)
    {
        perror("shamt");
        return 1;
    }

    limit=mem->limit;

    while(1){
        while(mem->cmd != 2){
            ;
        }

        int local_ball;
        local_ball=mem->ball;
        printf("We see ball: %d\n",local_ball);

        local_ball++;
        mem->ball=local_ball;
        mem->cmd=1;
        if(local_ball>limit)
        {
            break;
        }

    }

   shmdt(mem);




    return 0;
}
