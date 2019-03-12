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

TEST_CASE("Collective communications - split")
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    bool const is_apple = rank % 3 == 0;
    SECTION("split 1:2 and keep same process order")
    {
        // Create split communicator apple_orange
        // Note this will be different on different processes!
        MPI_Comm apple_orange;
        MPI_Comm_split(MPI_COMM_WORLD, is_apple ? 0 : 1, rank, &apple_orange);

        // Check our rank and size are as expected in the new communicator
        int nrank, nsize;
        MPI_Comm_rank(apple_orange, &nrank);
        MPI_Comm_size(apple_orange, &nsize);

        int const div = (size - 1) / 3, napples = 1 + div;
        if (is_apple) {
           CHECK(nsize == napples);
           CHECK(nrank == rank / 3); // Our original rank was divisible by 3
        } else {
           CHECK(nsize == size - napples);
           CHECK(nrank == rank - 1 - (rank / 3)); // Remove earlier apples
        }

        // Ex. 3: Use one of the collective operations on a single group
        // E.g. the root of each group broadcasts its original rank
    }

    SECTION("Ex. 1: split 1:2 with key = -rank")
    {
        // Create split communicator apple_orange
        // Note this will be different on different processes!

        // Check our rank and size are as expected in the new communicator
    }

    SECTION("Ex. 2: split 1:1:2 and keep process order")
    {
    }
}
