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
    if(argc<2)
    {
        fprintf(stderr,"need max_ball\n");
        return -1;
    }

    char *tmp;
    unsigned long limit = strtoul(argv[1],&tmp,10);

    key_t key=ftok("/etc/fstab",'u');
    int id;
    id= shmget(key,sizeof(ping_pong_mem_t),IPC_CREAT|IPC_EXCL|0700);

    if(id<0)
    {
        perror("shmget");
        return 1;
    }

    int sem_id;
    sem_id = semget(key,5,IPC_CREAT|IPC_EXCL|0700);

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

    mem->ball=0;
    mem->limit=limit;
    mem->cmd=1;

    struct sembuf sem_buf;
    sem_buf.sem_num = CONNECT_SEM;
    sem_buf.sem_op = 1;
    sem_buf.sem_flg = 0;

    semop(sem_id,&sem_buf,1);

    sem_buf.sem_num = SERVER_SEM;
    sem_buf.sem_op = 1;
    semop(sem_id,&sem_buf,1);

    while(1){

        sem_buf.sem_num = SERVER_SEM;
        sem_buf.sem_op = -1;
        semop(sem_id,&sem_buf,1);

        int local_ball;
        local_ball=mem->ball;
        printf("We see ball: %d\n",local_ball);

        local_ball++;
        mem->ball=local_ball;
        //mem->cmd=2;

        sem_buf.sem_num = CLIENT_SEM;
        sem_buf.sem_op = 1;
        semop(sem_id,&sem_buf,1);

        if(local_ball>limit)
        {
            break;
        }

    }

   shmdt(mem);
   if(shmctl(id,IPC_RMID,NULL)<0)
   {
       perror("shmctl");
       return 1;
   }

   int err;
   err=semctl(sem_id,4,IPC_RMID);
   if(err < 0)
   {
       perror("semctl");
       return 1;
   }

   return 0;
}
