/*================================================================
* Filename:test2.c
* Author: KCN_yu
* Createtime:Mon 09 Nov 2020 06:43:01 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h>
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
        //msgrcv(msgid,(struct msgbuf*)(&message),MAX,1,0);
        msgrcv(msgid,(&message),MAX,1,0);
        if(message.data[0] == 'q') break;
        printf("\nprocess: %s\n",message.data);
    }
    return 0;
}
