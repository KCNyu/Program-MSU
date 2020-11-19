#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <sys/sem.h>

#define MESSAGE_SIZE 1024
#define WORK_COMMAND 0
#define STOP_COMMAND 1

/*
 * There are three semaphores:
 *
 * The semaphore with the number 0 guide write arctivity  of the
 * process called 'writer'
 *
 * The semaphore with number 1 manages processes 'readers'.
 * Unlocked value allows read shared memory.
 *
 * The semaphore with the number 2 manages processes 'readers'
 * process reader will be locked after it read from the shared memory.
 *
 */
#define WRITER_SEMAPHORE       0
#define READER_READ_SEMAPHORE  1
#define READER_READY_SEMAPHORE 2


struct sembuf wait_readers_and_lock_them[2]=
{
	{WRITER_SEMAPHORE,0,0},
	{READER_READ_SEMAPHORE,1,0}
};
struct sembuf decrease_writer_semaphore={WRITER_SEMAPHORE,-1,0};
/*
struct sembuf increase_writer_semaphore={WRITER_SEMAPHORE,1,0};
*/
struct sembuf wait_writer_and_lock_him[3]=
{
	{READER_READY_SEMAPHORE,0,0},
	{READER_READ_SEMAPHORE,0,0},
	{WRITER_SEMAPHORE,1,0}
};
struct sembuf read_confirmation_op[2]=
{
	{READER_READ_SEMAPHORE,1,0},
	{READER_READ_SEMAPHORE,0,0}
};
struct sembuf clear_reader_semaphore={READER_READ_SEMAPHORE,-1,0};
/*
#struct sembuf lock_reader_semaphore={READER_READ_SEMAPHORE,1,0};
*/

struct sembuf increase_ready_semaphore={READER_READY_SEMAPHORE,1,0};
struct sembuf decrease_ready_semaphore={READER_READY_SEMAPHORE,-1,0};
struct sembuf lock_on_ready={READER_READY_SEMAPHORE,0,0};

typedef struct 
{
        int command;
        char text[MESSAGE_SIZE];
} Shared_memory;

#endif

