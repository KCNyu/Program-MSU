#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI8Inter21");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int root;
	double buf;
	pt >> buf;
	MPI_Comm inter_server, inter_client, comm;
	MPI_Comm_get_parent(&inter_server);
	MPI_Comm_get_parent(&inter_client);
	bool created = true;
	char str[18] = "Debug/ptprj.exe";
	if (inter_server == MPI_COMM_NULL && inter_client == MPI_COMM_NULL)
	{

		MPI_Comm_spawn(str, NULL, 1, MPI_INFO_NULL, 0,
			MPI_COMM_WORLD, &inter_server, MPI_ERRCODES_IGNORE);
		MPI_Comm_spawn(str, NULL, size - 1, MPI_INFO_NULL, 0,
			MPI_COMM_WORLD, &inter_client, MPI_ERRCODES_IGNORE);
		root = 0;
		
		created = false;
	}
	else
	{
		root = MPI_ROOT;
	}
	if (created)
	{
		//Show(size);
		//Show(rank);
		char port[MPI_MAX_PORT_NAME];
		char s[9] = "password";
		if (size == 1)
		{
			
			MPI_Recv(&buf, 1, MPI_DOUBLE, 0, 0, inter_server, MPI_STATUSES_IGNORE);
			Show(buf);

			MPI_Open_port(MPI_INFO_NULL, port);
			MPI_Publish_name(s, MPI_INFO_NULL, port);
			

			MPI_Comm_accept(port, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &comm);
			int sz;
			MPI_Comm_remote_size(comm, &sz);
			//Show(sz);
		
			for (int i = 0; i < sz; i++)
			{
				MPI_Send(&buf, 1, MPI_DOUBLE, i, 0, comm);
			}

		}
		else
		{
			MPI_Recv(&buf, 1, MPI_DOUBLE, rank + 1, 0, inter_client, MPI_STATUSES_IGNORE);
			Show(buf);
			
			MPI_Lookup_name(s, MPI_INFO_NULL, port);

			MPI_Comm_connect(port, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &comm);
			
			double A;
			MPI_Recv(&A, 1, MPI_DOUBLE, 0, 0, comm, MPI_STATUSES_IGNORE);
			double sum = buf + A;
			Show(sum);
			MPI_Barrier(MPI_COMM_WORLD);
			MPI_Send(&sum, 1, MPI_DOUBLE, rank + 1, 0, inter_client);
		}
		
	}
	else
	{
		if (rank == 0)
		{
			MPI_Send(&buf, 1, MPI_DOUBLE, 0, 0, inter_server);
		}
		else
		{
			MPI_Send(&buf, 1, MPI_DOUBLE, rank - 1, 0, inter_client);
			double sum;
			MPI_Recv(&sum, 1, MPI_DOUBLE, rank - 1, 0, inter_client, MPI_STATUSES_IGNORE);
			pt << sum;
		}
	}
}
