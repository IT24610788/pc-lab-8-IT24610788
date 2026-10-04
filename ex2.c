#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    long long N = 10000000;
    long long local_sum = 0, global_sum = 0;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    // Calculate the range for each process
    long long chunk_size = N / size;
    long long start = rank * chunk_size + 1;
    long long end = (rank == size - 1) ? N : start + chunk_size - 1;

    // Calculate local sum
    for (long long i = start; i <= end; i++) {
        local_sum += i;
    }

    // Reduce all local sums to the global sum on the root process (rank 0)
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        end_time = MPI_Wtime();
        printf("Total sum from 1 to %lld is %lld\n", N, global_sum);
        printf("Execution Time: %f seconds\n", end_time - start_time); // 4. Print the time
    }

    MPI_Finalize();
    return 0;
}