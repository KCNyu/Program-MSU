/*================================================================
* Filename:client.cpp
* Author: KCN_yu
* Createtime:Mon 31 May 2021 10:52:33 PM CST
================================================================*/

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
using namespace std;

#define SERV_PORT 9527

int main(int argc, char *argv[])
{
    int cfd;
    int ret;
    char buf[BUFSIZ];

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if(cfd == -1){
        cerr << "socket error" << endl;
    }

    connect(cfd, reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr));


    while(true){
        char tmp[BUFSIZ];
        cin >> tmp;
        write(cfd, tmp, strlen(tmp));
        ret = read(cfd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, ret);
        cout << endl;
    }
    close(cfd);
    return 0;
}
