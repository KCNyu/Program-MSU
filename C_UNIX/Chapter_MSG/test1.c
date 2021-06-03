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
#include <sys/types.h>
#include <sys/sem.h>
#include <error.h>
#include <string.h>

#define MAX 256

struct{
    long msgtype;
    char data[MAX];
}message;

int main(int argc, char *argv[])
{
    key_t key;
    int msgid;
    char str[MAX];
    key = ftok("./test1.c",'s');
    msgid = msgget(key,IPC_CREAT);
    while(1){
        fgets(str,MAX,stdin);
        strcpy(message.data,str);
        if(str[0] == 'a'){
            message.msgtype = 1;
            //msgsnd(msgid,(struct msgbuf*)(&message),strlen(str)+1,0);
            msgsnd(msgid,(&message),strlen(str)+1,0);
        }
        else if(str[0] == 'b'){
            message.msgtype = 2;
            msgsnd(msgid,(struct msgbuf*)(&message),strlen(str)+1,0);
        }
        else if(str[0] == 'q'){
            message.msgtype = 1;
            msgsnd(msgid,(struct msgbuf*)(&message),strlen(str)+1,0);

            message.msgtype = 2;
            msgsnd(msgid,(struct msgbuf*)(&message),strlen(str)+1,0);
            sleep(3);
            msgctl(msgid,IPC_RMID,NULL);
            return 0;
        }
        break;
    }
    return 0;
}
