#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm28");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int A;
    pt >> A;

    int indexes_5[5] = {2,4,5,7,8};
    int edges_5[8] = {1,3,0,2,1,0,4,3};

    int indexes_origin[9] = { 4,6,7,9,10,12,13,15,16 };
    int edges_origin[16] = { 1,3,5,7,0,2,1,0,4,3,0,6,5,0,8,7 };
    int* indexes = new int[size];
    for (int i = 0; i < size; i++) {
        if (size == 5) indexes[i] = indexes_5[i];
        else indexes[i] = indexes_origin[i];
    }
    int* edges = new int[indexes[size - 1]];
    for (int i = 0; i < indexes[size - 1]; i++) {
        if (size == 5) edges[i] = edges_5[i];
        else edges[i] = edges_origin[i];
    }

    int reorder = false;

    
    MPI_Comm new_communicator;
    MPI_Graph_create(MPI_COMM_WORLD, size, indexes, edges, reorder, &new_communicator);
    if (new_communicator != MPI_COMM_NULL) {
        int my_number_of_neighbours;
        MPI_Graph_neighbors_count(new_communicator, rank, &my_number_of_neighbours);
        ShowLine("number: ", my_number_of_neighbours);
        int* neighbours = new int[my_number_of_neighbours];
        MPI_Graph_neighbors(new_communicator, rank, my_number_of_neighbours, neighbours);
        for (int i = 0; i < my_number_of_neighbours; i++) {
            if (neighbours[i] < size) MPI_Send(&A, 1, MPI_INT, neighbours[i], 0, new_communicator);         
        }
        for (int i = 0; i < my_number_of_neighbours; i++) {
            if (neighbours[i] < size) {
                int res;
                MPI_Recv(&res, 1, MPI_INT, neighbours[i], 0, new_communicator, MPI_STATUSES_IGNORE);
                pt << res;
            }
        }
    }
    // remote repo failed
    // try one more times.
}
