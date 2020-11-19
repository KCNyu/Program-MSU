#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <arpa/inet.h>

#include <unistd.h>


#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define TCP_PORT_NUMBER 5555

#define STR_SIZE 1024

char str[STR_SIZE];

char tmp_str[STR_SIZE];

int main(int argc,char **argv)
{
	int socket_id;
	struct protoent *protocol_record=NULL;
	struct hostent *host_record=NULL;
	struct sockaddr_in server_address;

	int sock_fd;

	fd_set set;

	int c;
	/*
	 struct timeval delay={10,0};
	*/

	if(argc<2)
	{
		printf("client server_ip\n");
		return -1;
	}
	 
	protocol_record=getprotobyname("tcp");
	/* printf("protocol id is : %d\n",protocol_record->p_proto); */
	socket_id=socket(PF_INET,SOCK_STREAM,protocol_record->p_proto);
	
		
	host_record=gethostbyname(argv[1]);
	if(host_record==NULL)
	{
		printf("Can't get address by name '%s'\n",argv[1]);
		return -1;
	}


	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(TCP_PORT_NUMBER);
        /*
	server_address.sin_addr.s_addr=inet_addr(argv[1]);
	*/
	memcpy
	(
	 	&server_address.sin_addr.s_addr,
		host_record->h_addr_list[0],
		host_record->h_length
	);
	

	printf("connecting to server\n");
	sock_fd=
	connect
	(
	 	socket_id,
		(struct sockaddr *)&server_address,
		sizeof(struct sockaddr_in)
	);

	if(sock_fd)
	{
		printf("Can't connect to server\n");
		return -1;
	}

	read(socket_id,str,18);
	str[16]='\0';
	if(strcmp(str,"Server. Welcome."))
	{
		printf("Incorrect server invatation\n");
		printf("Server tells '%s'\n",str);
		return -1;
	}

	printf("server connected\n");

	/*	
	FD_ZERO(&set);
	FD_SET(sock_fd,&set);
	*/

	while(fgets(str,STR_SIZE-1,stdin))
	{
		write(socket_id,str,strlen(str));
		/*
		if(select(1,&set,NULL,NULL,&delay)>0)
		{
			read(sock_fd,tmp_str,STR_SIZE-1);
			tmp_str[STR_SIZE-1]=0;
			printf("-- %s --\n",tmp_str);
		}
		*/

	}

	close(socket_id);

	return 0;

}

