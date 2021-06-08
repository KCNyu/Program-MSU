/*================================================================
* Filename:client.cpp
* Author: KCN_yu
* Createtime:Wed 06 Jan 2021 12:20:51 PM CST
================================================================*/

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>

#define MAX_MSG 65536
#define SVR_PORT 9999
#define SVR_ADDR "127.0.0.1"

using namespace std;

int main(int argc, char* argv[]){
    int client_socket=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(SVR_PORT);
	server_addr.sin_addr.s_addr=inet_addr(SVR_ADDR);

	if (connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
	{
        cerr << "Connection failure!" << endl;
		return -1;
	}
    cout << "Successfully connected to the server!" << endl;

    char message[MAX_MSG];
    char buf[MAX_MSG];
    memset(message,0,sizeof(message));
    memset(message,0,sizeof(buf));

    cout << "I am a client, I will send content to the server" << endl;
    cout << "If you want to quit the chat, please enter q or Q" << endl;

    while(1)
	{

        cout << "I sent to the server: ";
        fgets(buf,MAX_MSG,stdin);

        if (strlen(buf)==2)
		{
			if(buf[0] == 'q' || buf[0] == 'Q') break;
		}

        if(strlen(buf) != static_cast<size_t>(write(client_socket, buf, strlen(buf)))){
            cerr << "write() error!" << endl;
            exit(1);
        }

        if(read(client_socket, message, sizeof(message)) <= 0){
            cerr << "read() error!" << endl;
            exit(1);
        }

        cout << "The server told me: \n" << message << endl;

        memset(buf,0,MAX_MSG);
        memset(message,0,MAX_MSG);
	}
	close(client_socket);
    cout << "Server is closed" << endl;
    return 0;
}
