#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int world_rank, partner_rank;
    int ping_pong_count = 0;

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    /*int world_size;*/
    /*MPI_Comm_size(MPI_COMM_WORLD, &world_size);*/

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    partner_rank = (world_rank + 1) % 2;

    
    while (ping_pong_count < 10) {
        if (world_rank == ping_pong_count % 2) {
            ping_pong_count++;
            MPI_Send (&ping_pong_count, 1, MPI_INT, partner_rank, 0,
                    MPI_COMM_WORLD);
            printf ("%d sent ball %d to %d\n", world_rank, 
                    ping_pong_count, partner_rank);
        }
        else {
            MPI_Recv (&ping_pong_count, 1, MPI_INT, partner_rank, 0,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf ("%d received ball %d from %d\n", world_rank, 
                    ping_pong_count, partner_rank);
        }
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}
