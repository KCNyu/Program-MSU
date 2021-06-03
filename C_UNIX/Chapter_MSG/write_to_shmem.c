#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    _Atomic int cmd;
    char message[256];
} Mem;

int main()
{
    int shid;
    char str[256];
    Mem *mem;
    key_t key=("/etc/passwd",'r');
       
    shid=shmget(key,sizeof(Mem),0);
    if(shid == -1) { perror("shmget"); return 1; }

    mem=shmat(shid,NULL,0);
    if(mem == (void *)-1) { perror("shmat"); return 1;}
    
    if(fgets(str,256,stdin)==NULL)
    {
       return 0;
    }


    while(mem->cmd != 0)
    {
        sched_yield();
    }

    strncpy(mem->message,str,256);
    mem->cmd=1;

    shmdt(mem);
    return 0;
}
