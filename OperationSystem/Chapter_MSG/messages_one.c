#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "messages.h"

struct msgbuf message;


int main()
{
	key_t messages_queue_key;
	int msg_queue_id;
	char *error_string;
	ssize_t read_size;
	int ret_val=0;
	int flag;


	messages_queue_key=ftok("messsages_one",1);
	msg_queue_id=msgget(messages_queue_key,IPC_CREAT|0666);
	if(msg_queue_id==-1)
	{
		error_string=strerror(errno);		
		printf("Can't create messages queue because '%s'\n",error_string);
		return -1;
	}
	
	
	for(;;)
	{
		read_size=msgrcv(msg_queue_id,&message,MESSAGE_SIZE,CONFIRM_MESSAGE_TYPE,0);
		if(read_size!=MESSAGE_SIZE)
		{
			error_string=strerror(errno);
			printf("Can't read message from queue because '%s' \n",error_string); 
			ret_val -2;
			break;
		}
		
		if(!strcmp(message.mtext,"finish"))
		{
			printf("It's time to finish work\n");
			break;
		}
		
		printf("recv: %s\n",message.mtext);
				
		if(fgets(message.mtext, MESSAGE_SIZE ,stdin)==NULL)
		{
			printf("Unexpected end of file\n");
			ret_val=-3;
			break;		
		}		
		
		message.mtype=DEFAULT_MESSAGE_TYPE;	
		if(msgsnd(msg_queue_id,&message,MESSAGE_SIZE,0))
		{
			error_string=strerror(errno);
			printf("Can't send message because '%s'\n",error_string);
			ret_val=-4;
			break;
		}
	
	}	
	
	msgctl(msg_queue_id,IPC_RMID,NULL);
	return ret_val;
}

