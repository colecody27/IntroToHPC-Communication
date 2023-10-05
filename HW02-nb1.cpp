#include <stdio.h>
#include <iostream>
#include <mpi.h>
#include <string>

int main(int argc, char* argv[]){
    int rank, size;
    std::string value = "";

   //Initialize 
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    //Initialize status
    MPI_Request iReq;
    MPI_Status iStatus;

    double startTime, endTime;
    int length;
    if(rank == 0){
        //Start time and send message 
        startTime = MPI_Wtime();
        value = "Cody Cole";
        length = value.length();

        MPI_Isend(value.c_str(), length, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &iReq);
        MPI_Wait(&iReq, &iStatus);

        endTime = MPI_Wtime();
        std::cout << "Elapsed time for one way non-blocking communication: " << endTime - startTime << "\n";
        std::cout << "Value for one way non-blocking communication: " << value << "\n\n";
    } else if(rank == 1){
        MPI_Probe(0, 0, MPI_COMM_WORLD, &iStatus);
        MPI_Get_count(&iStatus, MPI_CHAR, &length);
        char *value_buffer = new char[length];
        //Start time and receive message 
        MPI_Irecv(value_buffer, length, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &iReq);
        MPI_Wait(&iReq, &iStatus);

    }

    MPI_Finalize();
    return 0;
}