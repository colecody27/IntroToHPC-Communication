#include <stdio.h>
#include <iostream>
#include <mpi.h>
#include <string>

int main(int argc, char* argv[]){
    int rank, size;

   //Initialize 
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    std::string value = "";


    double start, end;
    int length;
    /* TWO WAY BLOCKING COMMUNICATION */
    //Send and receive for Rank 0 
    if(rank == 0){
        start = MPI_Wtime();
        value = "Cody Cole";
        length = value.length();

        //Send message to rank 1
        MPI_Send(value.c_str(), length, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

        //Receive message from rank 1 and end time 
        char *value_buffer = new char[length];
        MPI_Recv(value_buffer, length, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        value = value_buffer;
        end = MPI_Wtime();

        std::cout << "Elapsed time for two way blocking communication: " << end - start << "\n";
        std::cout << "Value for two way blocking communication: " << value << "\n\n";
    }
    else if(rank == 1){
        //Receive message from rank 0
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &length);
        char *value_buffer = new char[length];
        MPI_Recv(value_buffer, length, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        std::string tempCal = value_buffer;

        //Send message to rank 0
        MPI_Send(tempCal.c_str(), length, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}