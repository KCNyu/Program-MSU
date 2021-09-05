/*================================================================
* Filename:test6.cpp
* Author: KCN_yu
* Createtime:Sun 05 Sep 2021 10:38:41 PM CST
================================================================*/

#include <iostream>
#include <cstring>
#include "mpi.h"
using namespace std;

#define LOG_INFO(format, ...)                                                                           \
{                                                                                                       \
    time_t t = time(0);                                                                                 \
    struct tm ttt = *localtime(&t);                                                                     \
    fprintf(stdout, "[INFO] [%4d-%02d-%02d %02d:%02d:%02d] [%s] [%s:%d] " format "\n",                     \
            ttt.tm_year + 1900, ttt.tm_mon + 1, ttt.tm_mday, ttt.tm_hour,        \
            ttt.tm_min, ttt.tm_sec, __FILE__, __FUNCTION__ , __LINE__, ##__VA_ARGS__);                            \
}

int main(int argc, char* argv[])
{
    int numprocs, myid, source;
    MPI_Status status;
    char message[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    if (myid != 0) {  //非0号进程发送消息
        strcpy(message, "Hello World!");
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 99,
            MPI_COMM_WORLD);
    }
    else {   // myid == 0，即0号进程接收消息
        for (source = 1; source < numprocs; source++) {
            MPI_Recv(message, 100, MPI_CHAR, source, 99,
                MPI_COMM_WORLD, &status);
            LOG_INFO("接收到第%d号进程发送的消息：%s\n", source, message);
        }
    }
    MPI_Finalize();
    return 0;
} /* end main */