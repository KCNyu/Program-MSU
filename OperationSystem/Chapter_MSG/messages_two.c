#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "messages.h"



struct msgbuf message;
struct msgbuf confirm_message;


int main()
{
	key_t messages_queue_key;
	int msg_queue_id;
	char *error_string;
	ssize_t read_size;
	int ret_val=0;
	int flag;
	
	message.mtype         = DEFAULT_MESSAGE_TYPE;
	confirm_message.mtype = CONFIRM_MESSAGE_TYPE;
	strcpy(confirm_message.mtext,"ok");

	messages_queue_key=ftok("messsages_one",1);
	msg_queue_id=msgget(messages_queue_key,0);
	if(msg_queue_id==-1)
	{
		error_string=strerror(errno);		
		printf("Can't  connect to the messages queue because '%s'\n",error_string);
		return -1;	
	}

	if(msgsnd(msg_queue_id,&confirm_message,MESSAGE_SIZE,0))
	{
		error_string=strerror(errno);
		printf("Can't send message because '%s'\n",error_string);
		return -4;		
	}

	for(;;)
	{
	
		read_size=msgrcv(msg_queue_id,&message,MESSAGE_SIZE,DEFAULT_MESSAGE_TYPE,0);
		if(read_size!=MESSAGE_SIZE)
		{
			error_string=strerror(errno);
			printf("Can't read message from queue because '%s' \n",error_string); 
			ret_val -2;
			break;
		}		
			
		if(!strcmp(message.mtext,"finish\n"))
		{
			strcpy(confirm_message.mtext,"finish");
			break;
			
		}

		printf("%s",message.mtext);
		
		
		if(msgsnd(msg_queue_id,&confirm_message,MESSAGE_SIZE,0))
		{
			error_string=strerror(errno);
			printf("Can't send message because '%s'\n",error_string);
			ret_val=-4;
			break;
		}

	}	

	if(msgsnd(msg_queue_id,&confirm_message,MESSAGE_SIZE,0))
	{
		error_string=strerror(errno);
		printf("Can't send message because '%s'\n",error_string);
		ret_val=-4;
	}

	return ret_val;
}

