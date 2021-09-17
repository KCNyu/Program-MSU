#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <error.h>
#include <string.h>
#include <signal.h>

#define MAX 256
int semid, shmid;
char* shmaddr;

void sigHndlr(int s){
    shmdt(shmaddr);
    shmctl(shmid,IPC_RMID,NULL);
    semctl(semid,0,IPC_RMID,(int) 0);
    printf("free!\n");
    exit(0);
}
int main(int argc, char *argv[])
{
    signal(SIGINT,sigHndlr);
    char str[MAX];
    key_t key;
    key = ftok("hello",'s');
    struct sembuf sops;
    semid = semget(key,1,0666|IPC_CREAT);
    shmid = shmget(key,MAX,0666|IPC_CREAT);
    shmaddr = (char*)shmat(shmid,NULL,0);
    semctl(semid,0,SETVAL,(int) 0);
    sops.sem_num = 0;
    sops.sem_flg = 0;
    do{
        sops.sem_op = -2;
        semop(semid,&sops,1);
        printf("waiting!\n");
        strcpy(str,shmaddr);
        sprintf(shmaddr,"num = %s\n",argv[1]);
        sops.sem_op = -1;
        semop(semid,&sops,1);
    }while(1);
    return 0;
}
