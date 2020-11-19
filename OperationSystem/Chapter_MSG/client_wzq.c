#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SERVER_SEM  3
#define CLIENT_SEM  2
#define CONNECT_SEM 4

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

    key_t key=ftok("/etc/fstab",'u');
    int id;
    id= shmget(key,sizeof(ping_pong_mem_t),0);

    if(id<0)
    {
        perror("shmget");
        return 1;
    }

    int sem_id;
    sem_id = semget(key,5,0);

    if(sem_id<0)
    {
        perror("semget");
        return 1;
    }

    ping_pong_mem_t *mem;
   
    mem = shmat(id,NULL,0);
    if(mem==(void*)-1)
    {
        perror("shamt");
        return 1;
    }

    struct sembuf sem_buf;
    sem_buf.sem_num = CONNECT_SEM;
    sem_buf.sem_op = -1;
    sem_buf.sem_flg = 0;

    semop(sem_id,&sem_buf,1);

    limit=mem->limit;
    while(1){

        sem_buf.sem_num = CLIENT_SEM;
        sem_buf.sem_op = -1;
        semop(sem_id,&sem_buf,1);
        
        int local_ball;
        local_ball=mem->ball;
        printf("We see ball: %d\n",local_ball);

        local_ball++;
        mem->ball=local_ball;

        sem_buf.sem_num = SERVER_SEM;
        sem_buf.sem_op = 1;
        semop(sem_id,&sem_buf,1);

        if(local_ball>limit)
        {
            break;
        }      
        
    }

    shmdt(mem);

    return 0;
}
