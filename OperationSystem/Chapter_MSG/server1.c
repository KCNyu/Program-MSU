#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <unistd.h>


#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define TCP_PORT_NUMBER 5555
#define NUM_CONNECTIONS 2  


void *handler(void *args);

int connections[NUM_CONNECTIONS];
struct sockaddr_in clients[NUM_CONNECTIONS];

pthread_t threads[NUM_CONNECTIONS];

pthread_mutex_t mutex;

int num_connected=0;

int main(void)
{
	int socket_id;
	struct protoent *protocol_record=NULL;
	struct sockaddr_in server_address;

	socklen_t len;

	int i;

	pthread_mutex_init(&mutex,NULL);

	protocol_record=getprotobyname("tcp");
	/* printf("protocol id is : %d\n",protocol_record->p_proto); */
	socket_id=socket(PF_INET,SOCK_STREAM,protocol_record->p_proto);

	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(TCP_PORT_NUMBER);
	server_address.sin_addr.s_addr=INADDR_ANY;

	if(bind(socket_id,(struct sockaddr *)&server_address,sizeof(struct sockaddr_in)))
	{
		printf("ERRR\n");
		return -1;
	}

	listen(socket_id,5);
	
	for(i=0;i<NUM_CONNECTIONS;i++)
	{
		connections[i]=-1;;
	}
	
	for(;;)
	{
		struct sockaddr_in tmp_addr;
		int tmp_fd;

		if(num_connected<NUM_CONNECTIONS)
		{
			
			for(i=0;i<NUM_CONNECTIONS;i++)
			{
				if(connections[i]==-1)
				{
					break;
				}
			}
		
		
			tmp_fd=accept(socket_id,(struct sockaddr *)&clients[i],&len);	
			connections[i]=tmp_fd;

			pthread_mutex_lock(&mutex);
				num_connected++;
			pthread_mutex_unlock(&mutex);
			
			if(pthread_create(&threads[i],NULL,handler,&connections[i]))
			{
				printf("Can't create thread\n");

				close(socket_id);
				return -1;
			}

		}
		else
		{
			tmp_fd=accept(socket_id,(struct sockaddr *)&tmp_addr,&len);
			write(tmp_fd,"Server.  Buisy. \n",18);
			close(tmp_fd);
		}
	}	

	return 0;

}

void *handler(void *args)
{
	int fd=*(int *)args;
	char character;
	write(fd,"Server. Welcome.\n",18);
	while(read(fd,&character,1))
	{
		if(character=='.')
		{
			printf("TCHK\n");
		}
	}

	close(fd);

	pthread_mutex_lock(&mutex);
		*(int *)args=-1;
		num_connected--;
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);

	return NULL;

}

