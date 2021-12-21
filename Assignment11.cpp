#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char **argv)
{
	int rank, size;
	MPI_Status status;
	int msg = 13;
	int recv = 0;

	MPI_Init(&argc, &argv);
	MPI_Request reqs[4];
	MPI_Status stats[4];
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) { //process sends the array
		MPI_Send(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, &status);
		cout << "Process 0 finishes and received message " << msg << endl;
	} else {
		int src = rank -1;
		int dest = (rank + 1) % size;
		MPI_Sendrecv_replace(&msg, 1, MPI_INT, dest, 0, src, 0, MPI_COMM_WORLD, &status);
		cout << "Process " << rank << " received a message " << msg << " from process: " << status.MPI_SOURCE << " and sent it to process " << dest << endl;
	}
	
	MPI_Finalize();
}