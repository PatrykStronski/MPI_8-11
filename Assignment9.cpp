#include <stdio.h>
#include <algorithm>
#include "mpi.h"

#define SIZE 1000000

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    double start, finish;
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int vec_base[SIZE];
    int vec_recv[SIZE];
    
    for (int i = 0; i<SIZE; i++) {
        vec_base[i] = 1;
    }

    MPI_Reduce(&vec_base[0], &vec_recv[0], SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    finish = MPI_Wtime();
    if (rank == 0) {
        cout<<"The results for the first 5 elems"<<endl;
        cout<<vec_recv[0]<<","<<vec_recv[1]<<","<<vec_recv[2]<<","<<vec_recv[3]<<","<<vec_recv[4]<<endl;
    }
    
    MPI_Finalize();
    return 0;
}