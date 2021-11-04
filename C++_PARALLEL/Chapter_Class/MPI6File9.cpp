#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File9");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char name[12];
    if (rank == 0) pt >> name;
    MPI_Bcast(name, 12, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_File f = MPI_FILE_NULL;
    int a = MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &f);
    if (a != MPI_SUCCESS) ShowLine("failed");

    MPI_Offset fileSize;
    MPI_File_get_size(f, &fileSize);
    int count = fileSize / 4;
    MPI_File_seek(f, rank * 4, MPI_SEEK_SET);
    int readCount = min(rank + 1, count-rank);
    int* buf = new int[readCount];
    MPI_File_read_all(f, buf, readCount, MPI_INT, MPI_STATUSES_IGNORE);
    for (int i = 0; i < readCount; i++) {
        pt << buf[i];
    }
}
