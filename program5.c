#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int number;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size < 2) {
        if (rank == 0) {
            printf("This program requires at least 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        // Process 0 sends a number to Process 1
        number = 42;
        printf("Process 0 is sending number %d to Process 1\n", number);
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        // Process 1 receives a number from Process 0
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received number %d from Process 0\n", number);
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}




run the program command (x64 Native tools cammand)
1.>cd /d "C:\4MW23CS107" (which path will be their code/ program that path copy and past hear)
2.C:\4MW23CS107>cl program5.c msmpi.lib
Microsoft (R) C/C++ Optimizing Compiler Version 19.44.35215 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

program5.c
Microsoft (R) Incremental Linker Version 14.44.35215.0
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:program5.exe
program5.obj
msmpi.lib

C:\4MW23CS107>mpiexec -n 2 program5.exe
Process 0 is sending number 42 to Process 1
Process 1 received number 42 from Process 0

C:\4MW23CS107>mpiexec -n 4 program5.exe
Process 1 received number 42 from Process 0
Process 0 is sending number 42 to Process 1

