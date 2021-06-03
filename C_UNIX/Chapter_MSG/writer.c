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



int semaphors_id;
int shm_id;
Shared_memory *mem;

void clear_ipc(void)
{
	mem->command=STOP_COMMAND;

	shmdt(mem);
	shmctl(shm_id,IPC_RMID,NULL);

	semctl(semaphors_id,WRITER_SEMAPHORE,       IPC_RMID);
	semctl(semaphors_id,READER_READ_SEMAPHORE,  IPC_RMID);
	semctl(semaphors_id,READER_READY_SEMAPHORE, IPC_RMID);



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
	
	int work_flag=1;
	unsigned short semaphore_value;

	struct sembuf unlock_ready_operation;
	unlock_ready_operation.sem_num=READER_READY_SEMAPHORE;
	unlock_ready_operation.sem_flg=0;

	key=ftok("writer",1);
	shm_id=shmget(key,sizeof(Shared_memory),IPC_CREAT|0666);
	if(shm_id==-1)
	{
		error_string=strerror(errno);		
		printf("Can't create shared memory because '%s'\n",error_string);
		return -1;
	}
	
	semaphors_id=semget(key,3,IPC_CREAT|0666);
	if(semaphors_id==-1)
	{
		error_string=strerror(errno);		
		printf("Can't create semaphors because '%s'\n",error_string);
		return -1;
	}
	
	mem=shmat(shm_id,NULL,0);
	if(mem == (void *)-1)
	{
		error_string=strerror(errno);
		printf("Can't get address '%s'\n",error_string);
		return -1;
	}

	signal(SIGINT,handler);
	
	mem->command=WORK_COMMAND;
	mem->text[0]='\0';
	
	printf("Welcome to the programm for data broadcasting\n\n");

	
	while(work_flag)
	{
		/*
		 * Waiting for readers read data and then lock readers,
		 *  because shared memory will be changed.
		 */
		semop(semaphors_id,wait_readers_and_lock_them,2);

		if(fgets(mem->text, MESSAGE_SIZE ,stdin)==NULL)
		{
			printf("By by\n");
			mem->command=STOP_COMMAND;
			work_flag=0;
		}
		
		/*
		 * Unlock readers
		 */
		semaphore_value=semctl(semaphors_id,READER_READY_SEMAPHORE,GETVAL,0);
		printf("semaphore_value=%d\n",semaphore_value);
		unlock_ready_operation.sem_op=-semaphore_value;
		semop(semaphors_id,&unlock_ready_operation,1);

		semop(semaphors_id,&clear_reader_semaphore,1);
		
				
	

		/* not WORK!!!
		if(semctl(semaphors_id,READER_READ_SEMAPHORE,SETVAL,0))
		{
			error_string=strerror(errno);
			printf("Can't get address '%s'\n",error_string);
			return -1;		
		}
		*/
	
	}	

	clear_ipc();
	
	return 0;
}

