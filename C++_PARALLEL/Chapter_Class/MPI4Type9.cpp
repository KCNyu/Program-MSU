#include "pt4.h"
#include "mpi.h"
#define MAX_SIZE 1000
void Solve()
{
    Task("MPI4Type9");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int* num1 = new int[size];
    double* num2 = new double[size];
    char packbuf[MAX_SIZE];
    int packsize, position;


    if (rank == 0) {    
        for (int i = 0; i < size; i++) {
            pt >> num1[i];
        }
        for (int i = 0; i < size; i++) {
            pt >> num2[i];
        }
        packsize = 0;
        MPI_Pack(num1, size, MPI_INT, packbuf, MAX_SIZE, &packsize, MPI_COMM_WORLD);
        MPI_Pack(num2, size, MPI_DOUBLE, packbuf, MAX_SIZE, &packsize, MPI_COMM_WORLD);
    }
    MPI_Bcast(&packsize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(packbuf, packsize, MPI_PACKED, 0, MPI_COMM_WORLD);
    if (rank != 0) {
        position = 0;
        MPI_Unpack(packbuf, packsize, &position, num1, size, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(packbuf, packsize, &position, num2, size, MPI_DOUBLE, MPI_COMM_WORLD);
        for (int i = 0; i < size; i++) {
            pt << num1[i];
        }
        for (int i = 0; i < size; i++) {
            pt << num2[i];
        }
    }
}
