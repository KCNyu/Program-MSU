#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <sched.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    _Atomic int cmd;
    char message[256];
} Mem;

int main()
{
    int shid;
    Mem *mem;
    key_t key=("/etc/passwd",'r');
       
    shid=shmget(key,sizeof(Mem),IPC_CREAT|IPC_EXCL|0600);
    if(shid == -1) { perror("shmget"); return 1; }

    mem=shmat(shid,NULL,0);
    if(mem == (void *)-1) { perror("shmat"); return 1;}
    
    mem->cmd=0;

    while(mem->cmd != 1)
    {
        sched_yield();
    }

    printf("we see: \"%s\"\n",mem->message);

    shmdt(mem);
    shmctl(shid,IPC_RMID,NULL);
    return 0;
}
