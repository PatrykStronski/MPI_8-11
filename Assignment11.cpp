#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char **argv)
{
	int rank, size;
	MPI_Status statusf, statusb;
	int msg_forward = 10;
	int msg_backward = -10;

	int recvf = 0;

	MPI_Init(&argc, &argv);
	MPI_Request reqs[4];
	MPI_Status stats[4];
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) { //process sends the array
		MPI_Send(&msg_forward, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&msg_backward, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD);

        MPI_Recv(&msg_forward, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, &statusf);
		MPI_Recv(&msg_backward, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &statusb);
	} else {
		int src = rank -1;
		int dest = (rank + 1) % size;

		MPI_Sendrecv_replace(&msg_forward, 1, MPI_INT, dest, 0, src, 0, MPI_COMM_WORLD, &statusf);
		MPI_Sendrecv_replace(&msg_backward, 1, MPI_INT, src, 0, dest, 0, MPI_COMM_WORLD, &statusb);
	}
	cout << "Process " << rank << " received a message " << msg_forward << " from process: " << statusf.MPI_SOURCE  << endl;
	cout << "Process " << rank << " received a message " << msg_backward << " from process: " << statusb.MPI_SOURCE  << endl;
	
	MPI_Finalize();
}