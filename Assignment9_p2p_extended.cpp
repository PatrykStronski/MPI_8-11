#include <stdio.h>
#include <algorithm>
#include "mpi.h"

#define SIZE 100

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

    for (int div = 2; div < SIZE; div *= 2) {
        if (rank % div != 0) {
            MPI_Send(&vec_base[0], SIZE, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
        } 

        if (rank % div == 0) {
            if (rank != size -1) {
                MPI_Recv(&vec_recv[0], SIZE, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
                for (int i = 0; i < SIZE; i++) vec_base[i] += vec_recv[i];
            }
            if (rank != 0) MPI_Send(&vec_base[0], SIZE, MPI_INT, (rank / div) * div, 1, MPI_COMM_WORLD);
        }
    }

    if (rank == 0) {
        MPI_Recv(&vec_recv[0], SIZE, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
            for (int i = 0; i < SIZE; i++) vec_base[i] += vec_recv[i];
        
        cout<<"The results for the first 5 elems"<<endl;
        cout<<vec_base[0]<<","<<vec_base[1]<<","<<vec_base[2]<<","<<vec_base[3]<<","<<vec_base[4]<<endl;
    }
    
    MPI_Finalize();
    return 0;
}