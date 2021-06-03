#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#define MESSAGE_SIZE 1024
#define DEFAULT_MESSAGE_TYPE 1
#define CONFIRM_MESSAGE_TYPE 2

struct msgbuf
{
        long mtype;
        char mtext[MESSAGE_SIZE];
};

#endif
