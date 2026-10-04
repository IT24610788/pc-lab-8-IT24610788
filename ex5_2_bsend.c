#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size;
    int data_to_send = 12345;
    int received_data = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("This program requires at least 2 processes.\n");
        MPI_Finalize();
        return 1;
    }

    // Allocate and attach user-defined buffer for MPI_Bsend
    int buffer_size = MPI_BSEND_OVERHEAD + sizeof(int);
    char* buffer = (char*)malloc(buffer_size);
    MPI_Buffer_attach(buffer, buffer_size);

    if (rank == 0) {
        printf("Rank 0: Sending %d using MPI_Bsend...\n", data_to_send);
        MPI_Bsend(&data_to_send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Rank 0: MPI_Bsend returned immediately without blocking.\n");
    } else if (rank == 1) {
        MPI_Recv(&received_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank 1: Successfully received %d\n", received_data);
    }

    // Detach and deallocate the buffer
    MPI_Buffer_detach(&buffer, &buffer_size);
    free(buffer);

    MPI_Finalize();
    return 0;
}