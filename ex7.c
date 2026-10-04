#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    int rank, size;
    long long total_iterations = 10000000;
    long long local_count = 0;
    long long global_count = 0;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Allocate and attach buffer for MPI_Bsend
    int buffer_size = MPI_BSEND_OVERHEAD + sizeof(long long);
    char* buffer = (char*)malloc(buffer_size);
    MPI_Buffer_attach(buffer, buffer_size);

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    long long local_iterations = total_iterations / size;
    srand((unsigned int)time(NULL) + rank * 1000);

    for (long long i = 0; i < local_iterations; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            local_count++;
        }
    }

    if (rank != 0) {
        // Exercise 7 Requirement: Use MPI_Bsend
        MPI_Bsend(&local_count, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    } else {
        global_count = local_count;
        MPI_Status status;
        for (int i = 1; i < size; i++) {
            long long temp_count = 0;
            // Kept from Exercise 6: MPI_ANY_SOURCE
            MPI_Recv(&temp_count, 1, MPI_LONG_LONG, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            global_count += temp_count;
        }

        double pi = 4.0 * ((double)global_count / (double)total_iterations);
        end_time = MPI_Wtime();

        printf("Exercise 7 (Bsend) - Estimated Pi = %f\n", pi);
        printf("Execution Time: %f seconds\n", end_time - start_time);
    }

    // Detach and release the buffer
    MPI_Buffer_detach(&buffer, &buffer_size);
    free(buffer);

    MPI_Finalize();
    return 0;
}