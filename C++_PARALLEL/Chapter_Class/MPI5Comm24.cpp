#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI5Comm24");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int input[2];
	if (rank == 0) {
		pt >> input[0] >> input[1];
	}
	MPI_Bcast(input, 2, MPI_INT, 0, MPI_COMM_WORLD);
	if (rank < input[0] * input[1]) {

		int dims[2] = { input[0], input[1] };
		int periods[2] = { false, true };
		int reorder = false;
		MPI_Comm cartesian_communicator;
		MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartesian_communicator);
		int M = input[0], N = input[1];
		int X, Y;
		pt >> X >> Y;
		if (X >= M) {
			pt << -1;
			return;
		}
		if (Y >= N) {
			Y -= N;
		}
		else if (Y < 0) {
			Y += N;
		}
		int my_rank = X*N+Y;
		//MPI_Comm_rank(cartesian_communicator, &my_rank);
		int my_coords[2];
		MPI_Cart_coords(cartesian_communicator, my_rank, 2, my_coords);

		ShowLine("myrank: ", my_rank);
		ShowLine("X: ", my_coords[0]);
		ShowLine("Y: ", my_coords[1]);
		//int temp_coords0[3] = { my_coords[0] - M,my_coords[0], my_coords[0] + M };
		int temp_coords1[3] = { my_coords[1] - N,my_coords[1], my_coords[1] + N };
		bool t1 = false;
		for (int i = 0; i < 3; i++) {
			if (temp_coords1[i] == Y) t1 = true;
		}
		if (X == my_coords[0] && t1) {
			pt << my_rank;
		}
		else {
			pt << -1;
		}

	}
}
