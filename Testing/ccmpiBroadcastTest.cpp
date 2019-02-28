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

TEST_CASE("Collective communications - broadcast")
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // The message to send
    std::string const peace = "I come in peace!";
    std::string message; // The received message

    if (rank == 0)
    {
        // Send to all
        int error = MPI_Bcast(
            (void*) peace.c_str(), peace.size() + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
        REQUIRE(error == MPI_SUCCESS);
        // We don't send to ourselves
        message = peace;
    }
    else
    {
        char buffer[256];
        int error = MPI_Bcast(buffer, 256, MPI_CHAR, 0, MPI_COMM_WORLD);
        REQUIRE(error == MPI_SUCCESS);
        message = std::string(buffer);
    }

    // Check the received message
    CHECK(message == peace);

    // Round-robin checking, each process in turn, for nicer output
    for (int i(0); i < size; ++i)
    {
        if (rank == i)
        {
            INFO("Current rank is " << rank);
            CHECK(message == peace);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
}
