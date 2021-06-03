#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>


#include <stdio.h>
#include <stdlib.h>

#define SEM_NUM_OFFSET 3

#define CLIENTS_SEM    0
#define SERVER_SEM     1

struct sembuf unlock_client = {CLIENTS_SEM, 1,0};
struct sembuf lock_client   = {CLIENTS_SEM,-1,0};
struct sembuf lock_server   = {SERVER_SEM,-1,0};
struct sembuf unlock_server = {SERVER_SEM, 1,0};


typedef struct
{
    int finish;
} Mem;


int main(int argc, char **argv)
{
    int semid, shid;
    int num_philosophers;
    int i;

    Mem *mem;

    struct sembuf oper;
    oper.sem_flg=0;


    if(argc<2)
    {
        fprintf(stderr,"We need number of philosopers in first program parameter\n");
        return 1;
    }

    num_philosophers=atoi(argv[1]);
    if(num_philosophers<2)
    {
        fprintf(stderr,"Number of philosophers must be >=2\n");
        return 1;
    }


    key_t key=("/root/Program",'f');

    //shid=shmget(key,sizeof(Mem),IPC_CREAT|IPC_EXCL|0600);
    shid=shmget(key,sizeof(Mem),IPC_CREAT|0600);
    if(shid == -1) { perror("shmget"); return 1; }


    //semid=semget(key,num_philosophers+3,IPC_CREAT|IPC_EXCL|0600);
    semid=semget(key,num_philosophers+3,IPC_CREAT|0600);
    if(semid == -1) { perror("semget"); return 1; }


    mem=shmat(shid,NULL,0);
    if(mem == (void *)-1) { perror("shmat"); return 1;}


    mem->finish=0;


    for(i=0; i<num_philosophers; i++)
    {
        oper.sem_num=i+SEM_NUM_OFFSET;
        oper.sem_op=1; /* Разблокируем палочки */
        semop(semid, &oper, 1);
    }

    /*
     * Разрешаем философам начать обедать.
     */
    oper.sem_num=CLIENTS_SEM;
    oper.sem_op=num_philosophers;
    semop(semid, &oper, 1);


    semop(semid, &lock_server, 1);

    shmdt(mem);
    shmctl(shid,IPC_RMID,NULL);
    semctl(semid,0,IPC_RMID);
    return 0;
}

