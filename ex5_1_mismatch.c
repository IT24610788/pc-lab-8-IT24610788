#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    int data = 42;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("This program requires at least 2 processes.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        printf("Rank 0: Sending data to Rank 1...\n");
        // Sends to rank 1
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Rank 0: Send completed.\n");
    } else if (rank == 1) {
        int received_data;
        printf("Rank 1: Waiting to receive from Rank 2 (Mismatch!)...\n");
        // Expects from rank 2 instead of rank 0
        MPI_Recv(&received_data, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank 1: Received data: %d\n", received_data);
    }

    MPI_Finalize();
    return 0;
}