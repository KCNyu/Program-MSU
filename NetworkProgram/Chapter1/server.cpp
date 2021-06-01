/*================================================================
 * Filename:server.cpp
 * Author: KCN_yu
 * Createtime:Mon 31 May 2021 10:34:06 PM CST
 ================================================================*/

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

#define SERV_PORT 9527

int main(int argc, char *argv[])
{
    int lfd = 0, cfd = 0;
    int ret;
    char buf[BUFSIZ], client_IP[1024];

    struct sockaddr_in serv_addr, clit_addr;
    socklen_t clit_addr_len;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1){
        cerr << "sorcket error" << endl;
    }

    bind(lfd, reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr));

    listen(lfd, 128);

    clit_addr_len = sizeof(clit_addr);
    cfd = accept(lfd, reinterpret_cast<sockaddr*>(&clit_addr), &clit_addr_len);
    if(cfd == -1){
        cerr << "accept error" << endl;
    }
    cout << "clit_addr_len = " << clit_addr_len << endl;
    printf("client ip:%s port:%d\n",inet_ntop(AF_INET, &clit_addr.sin_addr.s_addr, client_IP, sizeof(client_IP)),
            ntohs(clit_addr.sin_port));
    while(true){
        ret = read(cfd, buf, sizeof(buf));
        if(ret == 0) break;
        write(STDOUT_FILENO, buf, ret);
        cout << endl;

        for(int i = 0; i < ret; i++){
            buf[i] = toupper(buf[i]);
        }

        write(cfd, buf, ret);
    }

    close(cfd);
    close(lfd);
    cout << "finish!" << endl;

    return 0;
}
