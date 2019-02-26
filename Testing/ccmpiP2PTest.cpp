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

TEST_CASE("Point to point communications")
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    SECTION("Blocking synchronous send") {
        std::string const peace = "I come in peace!";
        if (rank == 0) {
            int const error = MPI_Ssend(
                (void*) peace.c_str(), peace.size() + 1, MPI_CHAR, 1, 42, MPI_COMM_WORLD);
            // Here, we guarantee that Rank 1 has received the message.
            REQUIRE(error ==  MPI_SUCCESS);
        }
        if (rank == 1) {
            char buffer[256];
            int const error = MPI_Recv(
                buffer, 256, MPI_CHAR, 0, 42, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            REQUIRE(error ==  MPI_SUCCESS);
            CHECK(std::string(buffer) == peace);
        }
    }
}
