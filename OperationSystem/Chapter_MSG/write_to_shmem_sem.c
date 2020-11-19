#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int shid, semid;
    char str[256];
    Mem *mem;
    key_t key=("/etc/passwd",'s');
       
    shid=shmget(key,sizeof(Mem),0);
    if(shid == -1) { perror("shmget"); return 1; }

    semid=semget(key,2,0);
    if(semid == -1) { perror("semget"); return 1; }

    mem=shmat(shid,NULL,0);
    if(mem == (void *)-1) { perror("shmat"); return 1;}
    
    if(fgets(str,256,stdin)==NULL)
    {
       return 0;
    }

    semop(semid, &lock_client, 1);

    strncpy(mem->message,str,256);
    
    semop(semid, &unlock_server, 1);

    shmdt(mem);
    return 0;
}
