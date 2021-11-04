#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI4Type19");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int N;
    pt >> N;
    if (rank != 0) {
        int P;
        pt >> P;
        int sz = 3 * N - 2;
        int* B = new int[sz];
        for (int i = 0; i < sz; i++) {
            pt >> B[i];
        }
        MPI_Send(B, sz, MPI_INT, 0, P, MPI_COMM_WORLD);
    }
    else {
        int sz = N * N*(size-1);
        int* A = new int[sz];
        int* P = new int[size - 1];
        for (int i = 0; i < sz; i++) A[i] = 0;
        for (int i = 1; i < size; i++) {
            MPI_Status status;
            MPI_Probe(i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            P[i - 1] = status.MPI_TAG;
        }
        MPI_Datatype MPI_INDEX;
        int count = N;
        int* blocklengths = new int[N];
        for (int i = 0; i < N; i++) {
            if (i == 0 || i == N - 1) blocklengths[i] = N;
            else blocklengths[i] = 1;
        }
        int* displacements = new int[N];
        for(int i = 0; i < N; i++) {
            if (i == 0) displacements[i] = 0;
            else if (i == 1) displacements[i] = N * 4 - 2;
            else displacements[i] = displacements[i - 1] + 3 * N - 1;
        }
        MPI_Type_indexed(count, blocklengths, displacements, MPI_INT, &MPI_INDEX);
        MPI_Type_commit(&MPI_INDEX);
        for (int i = 1; i < size; i++) {
            MPI_Recv(A + P[i - 1], 1, MPI_INDEX, i, P[i - 1], MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        }
        for (int i = 0; i < sz; i++) pt << A[i];
    }
}
