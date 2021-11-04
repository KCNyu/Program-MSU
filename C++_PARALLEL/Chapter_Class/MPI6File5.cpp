#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File5");
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

    if (rank != 0) {
        int buf;
        MPI_Offset offset;
        do {
            MPI_File_read(f, &buf, 1, MPI_INT, MPI_STATUSES_IGNORE);
            pt << buf;
        } while (buf != rank);
        MPI_File_get_position(f, &offset);
        ShowLine("offset: ", (int)offset);
        MPI_File_seek(f, -offset, MPI_SEEK_END);
        /*
        MPI_File_get_position(f, &offset);
        ShowLine("offset: ", (int)offset);
        */
        for (int i = 0; i < offset / 4; i++) {
            MPI_File_read(f, &buf, 1, MPI_INT, MPI_STATUSES_IGNORE);
            pt << buf;
        }
        /*
        while (true) {
            int temp = MPI_File_read(f, &buf, 1, MPI_INT, MPI_STATUSES_IGNORE);
            if (temp != MPI_SUCCESS) break;
            pt << buf;
        }
        */
    }
}
