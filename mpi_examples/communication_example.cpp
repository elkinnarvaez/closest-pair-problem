#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){
    int rank, data[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0){
        MPI_Send(data, 3, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(data, 3, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(int i = 0; i < 3; i++){
            printf("%d ", data[i]);
        }
        printf("\n");
    }
    else if(rank == 1){
        MPI_Recv(data, 3, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(int i = 0; i < 3; i++){
            printf("%d ", data[i]);
        }
        printf("\n");
        data[0] = 5;
        MPI_Send(data, 3, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}