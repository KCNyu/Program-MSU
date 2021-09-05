/*================================================================
* Filename:test5.cpp
* Author: KCN_yu
* Createtime:Sun 05 Sep 2021 10:12:02 PM CST
================================================================*/

#include <iostream>
#include "omp.h"
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
#define NUM_THREADS 1
int main(int argc,char*argv[])
{
    int my_rank,numprocs,thread_id,nthreads;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
     #pragma omp parallel num_threads(NUM_THREADS) private(thread_id, nthreads)
    {
        thread_id=omp_get_thread_num();
        nthreads=omp_get_num_threads();
        LOG_INFO("Hello,The World!from thread number %d (on %d)for the MPI process number %d (on %d)\n",thread_id, nthreads, my_rank, numprocs);
    }
    MPI_Finalize();
    LOG_INFO("end");
    return 0;
}
// mpicc demo2.c -o demo2 -fopenmp
// mpirun ./demo2 -up 6