/*================================================================
*   Copyright (C) 2021 ChenXuandong Ltd. All rights reserved.
*   
*   FileName:newclient.cpp
*   Author:ChenXuandong
*   Data:2021年01月10日
*   Description：
*
================================================================*/

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>

#define TCP_PORT_NUMBER 5555
#define MAX_SIZE 32767

using namespace std;

int main(int argc, char* argv[]){
/*	if (argc == 1)
	{
        cerr << "use this with port and adress" << endl;
		return -1;
	}*/
    int client_socket=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
//	server_addr.sin_port=htons(atoi(argv[1]));
	server_addr.sin_port=htons(TCP_PORT_NUMBER);
//  server_addr.sin_addr.s_addr=inet_addr(argv[2]);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	if (connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
	{
        cerr << "Connection failure!" << endl;
		return -1;
	}
    char message[MAX_SIZE];
    char buf[MAX_SIZE];
    memset(message,0,sizeof(message));
    memset(message,0,sizeof(buf));
    cout << "I am a client, I will send content to the server" << endl;
    cout << "If you want to quit the chat, please enter q or Q" << endl;
    cout<<"You can try:"<<endl;
	cout<<"SHOW"<<endl;
	cout<<"FIND ...    "<<"FIND Group ...    "<<"FIND Age ...    "<<"FIND Rating ..."<<endl;
	cout<<"ADD Rating ... Fio ... Country ... Age ... Gender ... Group ..."<<endl;
	cout<<"DEL Rating ..."<<endl;
	cout<<"               ...  this is what can input"<<endl;
	cout<<"                  some examples:"<<endl;
	cout<<"SHOW"<<endl;
	cout<<"FIND China"<<endl;
	cout<<"FIND Female"<<endl;
	cout<<"FIND Rating 123456"<<endl;
	cout<<"FIND Group 3"<<endl;
	cout<<"FIND Age 20"<<endl;
	cout<<"ADD Rating 123456 Fio testfio Country China Age 20 Gender Male Group 3"<<endl;
	cout<<"DEL Rating 123456"<<endl;
    while(1)
	{
		fgets(buf,MAX_SIZE,stdin);
        if (strlen(buf)==2)
		{
			if(buf[0] == 'q' || buf[0] == 'Q') break;
		}
        if(strlen(buf) != write(client_socket, buf, strlen(buf))){
            cerr << "write() error!" << endl;
            exit(-1);
        }
        if(read(client_socket, message, sizeof(message)) <= 0){
            cerr << "read() error!" << endl;
            exit(-1);
        }
        cout << "Message From the server : " <<endl;
		cout<<message << endl;
        memset(buf,0,MAX_SIZE);
        memset(message,0,MAX_SIZE);
	}
	close(client_socket);
    cout<<"Server close"<<endl;
    return 0;
}
