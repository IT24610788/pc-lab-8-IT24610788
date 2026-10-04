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

    // Synchronize processes and start the timer on the root process
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    long long local_iterations = total_iterations / size;

    // Seed the random number generator uniquely per rank
    srand((unsigned int)time(NULL) + rank * 1000);

    // Monte Carlo simulation: generate points in [0, 1) x [0, 1)
    for (long long i = 0; i < local_iterations; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            local_count++;
        }
    }

    if (rank != 0) {
        // Worker processes send local count to rank 0
        MPI_Send(&local_count, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    } else {
        // Rank 0 initializes with its own count and gathers counts from workers
        global_count = local_count;
        for (int src = 1; src < size; src++) {
            long long temp_count = 0;
            MPI_Recv(&temp_count, 1, MPI_LONG_LONG, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            global_count += temp_count;
        }

        // Calculate Pi: (4 * points_inside) / total_points
        double pi = 4.0 * ((double)global_count / (double)total_iterations);

        end_time = MPI_Wtime();

        printf("Estimated Pi = %f\n", pi);
        printf("Execution Time: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}