/*================================================================
* Filename:dup.cpp
* Author: KCN_yu
* Createtime:Sun 23 May 2021 04:03:15 PM CST
================================================================*/

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main(int argc, char *argv[])
{
    int fd = open("tmp.txt",O_RDWR|O_CREAT,0644);
    int newfd = dup(fd);
    cout << "fd: " << fd << endl;
    cout << "newfd: " << newfd << endl;

    close(fd);
    write(newfd,"123456",6);
    close(fd);
    close(newfd);
    return 0;
}
