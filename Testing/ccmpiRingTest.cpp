/*=============================================================================

  CMAKECATCHMPI: A software package to demo MPI with CMake, CTest and Catch.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "ccmpiCatchMain.h"
#include <iostream>
#include <mpi.h>

TEST_CASE("Ring communications - blocking synchronous")
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // This case only works with an even number of processes
    REQUIRE(size % 2 == 0);

    // The message to send
    int message = rank*rank;

    // Define the ring
    int left = rank - 1;
    int right = rank + 1;
    if (rank == 0) {
        left = size - 1;
    }
    if (rank == size - 1) {
        right = 0;
    }

    SECTION("Blocking synchronous")
    {
        // Even processes send then receive; odd ones receive then send
        int received = -7;
        if (rank % 2 == 0)
        {
            int error = MPI_Ssend(
                &message, 1, MPI_INT, left, rank, MPI_COMM_WORLD);
            REQUIRE(error == MPI_SUCCESS);

            error = MPI_Recv(
                &received, 1, MPI_INT, right, right, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            REQUIRE(error == MPI_SUCCESS);
        }
        if (rank % 2 == 1)
        {
            int error = MPI_Recv(
                &received, 1, MPI_INT, right, right, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            REQUIRE(error == MPI_SUCCESS);

            error = MPI_Ssend(
                &message, 1, MPI_INT, left, rank, MPI_COMM_WORLD);
            REQUIRE(error == MPI_SUCCESS);
        }
        // Check the expected message was received
        REQUIRE( received == right*right );
    }
}


TEST_CASE("Ring communications")
{
    // These versions work with any number of processes, so are in a separate test case
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // The message to send
    int message = rank*rank;

    // Define the ring
    int left = rank - 1;
    int right = rank + 1;
    if (rank == 0) {
        left = size - 1;
    }
    if (rank == size - 1) {
        right = 0;
    }

    SECTION("Asynchronous")
    {
        // Everyone sets up their messages to send
        MPI_Request send_req;
        int error = MPI_Isend(
            &message, 1, MPI_INT, left, rank, MPI_COMM_WORLD, &send_req);
        REQUIRE(error == MPI_SUCCESS);

        // Recv acts as our sync-barrier
        int received = -7;
        error = MPI_Recv(
            &received, 1, MPI_INT, right, right, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        REQUIRE(error == MPI_SUCCESS);

        // But let's check explicitly that our send completed
        int completed;
        error = MPI_Test(&send_req, &completed, MPI_STATUS_IGNORE);
        REQUIRE(error ==  MPI_SUCCESS);
        REQUIRE(completed == true);

        // Check the expected message was received, as above
        REQUIRE( received == right*right );
    }

    SECTION("Sendrecv")
    {
        // For you to implement...
    }
}
