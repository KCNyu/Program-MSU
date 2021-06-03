/*================================================================
* Filename:test1.c
* Author: KCN_yu
* Createtime:Mon 09 Nov 2020 06:43:01 PM CST
================================================================*/

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

#define MAX 256

int main(int argc, char *argv[])
{
    char str[MAX];
    char* shmaddr;
    key_t key;
    key = ftok("./test3.c",'s');
    int semid, shmid;
    struct sembuf sops;
    semid = semget(key,1,0666|IPC_CREAT);
    shmid = shmget(key,MAX,0666|IPC_CREAT);
    shmaddr = (char*)shmat(shmid,NULL,0);
    semctl(semid,0,SETVAL,(int) 0);
    sops.sem_num = 0;
    sops.sem_flg = 0;
    do{
        if(fgets(str,MAX,stdin) == NULL){
            strcpy(str,"Q");
        }
        strcpy(shmaddr,str);
        sops.sem_op = 6;
        semop(semid,&sops,1);
        sops.sem_op = 0;
        semop(semid,&sops,1);
    }while(str[0] != 'Q');
    shmdt(shmaddr);
    shmctl(shmid,IPC_RMID,NULL);
    semctl(semid,0,IPC_RMID,(int) 0);
    return 0;
}
