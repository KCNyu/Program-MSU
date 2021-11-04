#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI5Comm31");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int A;
	pt >> A;
	/*
	int sources[1] = { rank };
	int degrees[1];
	if (rank % 3 == 0) degrees[0] = 3;
	else if (rank % 3 == 1) degrees[0] = 1;
	else if (rank % 3 == 2) degrees[0] = 0;
	int* destinations = new int[degrees[0]];
	for (int i = 0; i < degrees[0]; i++) {
		destinations[i] = rank + i;
		if (destinations[i] > size) destinations[i] = 0;
	}
	*/

	MPI_Comm new_comm;
	if (rank == 0) {

		//int sources[12] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
		//int degrees[12] = { 3,1,0,3,1,0,3,1,0,3,1,0 };
		//int destinations[16] = { 1,2,3,2,4,5,6,5,7,8,9,8,10,11,0,11 };

		int* sources = new int[size];
		int* degrees = new int[size];
		int sum_dest = 0;
		for (int i = 0; i < size; i++) {
			sources[i] = i;
			if (i % 3 == 0) degrees[i] = 3;
			else if (i % 3 == 1) degrees[i] = 1;
			else if (i % 3 == 2) degrees[i] = 0;
			sum_dest += degrees[i];
		}
		int* destinations = new int[sum_dest];
		int index = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 1; j <= degrees[i]; j++) {
				destinations[index] = i + j;
				if (destinations[index] == size) destinations[index] = 0;
				index++;
			}
		}

		int reorder = false;
		MPI_Dist_graph_create(MPI_COMM_WORLD, size, sources, degrees, destinations, MPI_UNWEIGHTED, MPI_INFO_NULL, reorder, &new_comm);
	}
	else {
		int* sources = nullptr;
		int* degrees = nullptr;
		int* destinations = nullptr;
		int reorder = false;
		MPI_Dist_graph_create(MPI_COMM_WORLD, 0, sources, degrees, destinations, MPI_UNWEIGHTED, MPI_INFO_NULL, reorder, &new_comm);
	}



	//MPI_Dist_graph_create(MPI_COMM_WORLD, 1, sources, degrees, destinations, MPI_UNWEIGHTED, MPI_INFO_NULL, false, &new_comm);
	if (new_comm != MPI_COMM_NULL) {
		int indegree, outdegree, weight;
		MPI_Dist_graph_neighbors_count(new_comm, &indegree, &outdegree, &weight);
		int* neighbors_source = new int[indegree];
		int* neighbors_dest = new int[outdegree];
		int* weight_source = new int[indegree];
		int* weight_dest = new int[outdegree];
		MPI_Dist_graph_neighbors(new_comm, indegree, neighbors_source, weight_source, outdegree, neighbors_dest, weight_dest);
		for (int i = 0; i < outdegree; i++) {
			if (neighbors_dest[i] == rank) continue;
			MPI_Send(&A, 1, MPI_INT, neighbors_dest[i], 0, new_comm);
		}
		ShowLine("indegree: ", indegree);
		ShowLine("outdegree: ", outdegree);

		int res, sum = A;
		for (int i = 0; i < indegree; i++) {
			if (neighbors_source[i] == rank) continue;
			MPI_Recv(&res, 1, MPI_INT, neighbors_source[i], 0, new_comm, MPI_STATUSES_IGNORE);
			sum += res;
		}
		pt << sum;
	}
}
