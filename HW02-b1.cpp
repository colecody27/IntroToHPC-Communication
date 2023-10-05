#include <stdio.h>
#include <iostream>
#include <mpi.h>
#include <string>

int main(int argc, char* argv[]){
    int rank, size;

   //Initialize MPI 
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    //Initialize charging times 
    int charging_times [8] = {30, 10, 70, 10, 40, 10, 60, 30}; 

    

    /* ONE WAY BLOCKING COMMUNICATION */
    //SEND 
    double start, end;
    int length;
    if(rank == 0){
        start = MPI_Wtime();
        value = "Cody Cole";
        length = value.length();

        //number = 15;
        //Send message to rank 1 and get start time 
        //MPI_Send(&value, value.size(), MPI_UNSIGNED_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Send(value.c_str(), length, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        end = MPI_Wtime();

        std::cout << "Elapsed time for one way blocking communication: " << end - start << "\n";
        std::cout << "Value for one way blocking communication: " << value << "\n\n";
    }
    //RECEIVE
    else if(rank == 1){
        //Receive message from rank 0
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &length);

        char *value_buffer = new char[length];
        MPI_Recv(value_buffer, length, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    


    // /* TWO WAY BLOCKING COMMUNICATION */
    // //Send and receive for Rank 0 
    // if(rank == 0){
    //     //value = "New Cody";
    //     number = 25;
        
    //     //Send message to rank 1 and start time 
    //     start = MPI_Wtime();
    //     // MPI_Send(&value, value.size(), MPI_UNSIGNED_CHAR	, 1, 0, MPI_COMM_WORLD);
    //     MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

    //     //Receive message from rank 1 and end time 
    //     // MPI_Recv(&value, 2, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //     MPI_Recv(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //     end = MPI_Wtime();

    //     std::cout << "Elapsed time for two way blocking communication: " << end - start << "\n";
    //     std::cout << "Value for two way blocking communication: " << number << "\n\n";
    // }
    // //Send and receive for Rank 1 
    // else if(rank == 1){
    //     //Receive message from rank 0 and get end time 
    //     // MPI_Recv(&value, value.size(), MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //     MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    //     //Send message to rank 0
    //     MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    //     // MPI_Send(&value, value.size(), MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
    // }

    MPI_Finalize();
    return 0;
}