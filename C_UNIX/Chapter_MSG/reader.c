#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "memory.h"

Shared_memory *mem;
int semaphors_id;
int shm_id;

int read_flag;
int ready_flag;

void clear_ipc(void)
{
	int semval;
	shmdt(mem);

	semval=semctl(semaphors_id,WRITER_SEMAPHORE,GETVAL);
	if(semval&&read_flag)
	{
		semop(semaphors_id,&decrease_writer_semaphore,1);
	}
	semval=semctl(semaphors_id,READER_READY_SEMAPHORE,GETVAL);
	if(semval&&ready_flag)
	{
		semop(semaphors_id,&decrease_ready_semaphore,1);
	}

	return;
}


void handler(int s)
{
	clear_ipc();
	exit(-1);
}



int main()
{
	key_t key;
	
	char *error_string;
	
	read_flag=0;


	key=ftok("writer",1);
	shm_id=shmget(key,sizeof(Shared_memory),0);
	if(shm_id==-1)
	{
		error_string=strerror(errno);		
		printf("Can't connect to shared memory because '%s'\n",error_string);
		return -1;
	}
	
	semaphors_id=semget(key,3,0);
	if(semaphors_id==-1)
	{
		error_string=strerror(errno);		
		printf("Can't connect to the semaphors because '%s'\n",error_string);
		return -1;
	}
	
	mem=(Shared_memory *)shmat(shm_id,NULL,0);
	if(mem==(void *)-1)
	{
		error_string=strerror(errno);
		printf("Can't get address '%s'\n",error_string);
		return -1;
	}
	
	signal(SIGINT,handler);	
	
	for(;;)
	{
		/*
		 * Waiting for writer write data and then lock him.
		 * Readers will read data. 
		 */
		semop(semaphors_id, wait_writer_and_lock_him,3);
		ready_flag=0;
		read_flag=1;
		if(mem->command==STOP_COMMAND)
		{
			break;
		}
		
		printf("%s",mem->text);
	
		/*
		 * Inform writer on reading finish
		 */
		semop(semaphors_id,&increase_ready_semaphore,1);
		ready_flag=1;
		semop(semaphors_id,&decrease_writer_semaphore,1);
		read_flag=0;
				
		/* This variant is not work! (see 'wait_writer_and_lock_him'
		 * operation. with commands 1 and 2 (except 0).)
		 *
		semop(semaphors_id,&lock_on_ready,1);
		*/
		
		
	
	}	
	
	shmdt(mem);

	
	return 0;
}

