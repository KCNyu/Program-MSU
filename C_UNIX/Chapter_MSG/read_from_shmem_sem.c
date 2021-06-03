#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <sched.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char message[256];
} Mem;

#define SERVER_SEM 1
#define CLENTS_SEM 0

struct sembuf unlock_client = {CLENTS_SEM, 1,0};
struct sembuf lock_client   = {CLENTS_SEM,-1,0};
struct sembuf lock_server   = {SERVER_SEM,-1,0};
struct sembuf unlock_server = {SERVER_SEM, 1,0};

int main()
{
    int shid,semid;
    Mem *mem;
    key_t key=("/etc/passwd",'s');
       
    shid=shmget(key,sizeof(Mem),IPC_CREAT|IPC_EXCL|0600);
    if(shid == -1) { perror("shmget"); return 1; }
  
    semid=semget(key,2,IPC_CREAT|IPC_EXCL|0600);
    if(semid == -1) { perror("semget"); return 1; }


    mem=shmat(shid,NULL,0);
    if(mem == (void *)-1) { perror("shmat"); return 1;}

    semop(semid, &unlock_client, 1);
    semop(semid, &lock_server, 1);

    printf("we see: \"%s\"\n",mem->message);

    shmdt(mem);
    shmctl(shid,IPC_RMID,NULL);
    semctl(semid,0,IPC_RMID);
    return 0;
}

