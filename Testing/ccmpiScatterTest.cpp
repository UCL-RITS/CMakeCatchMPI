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

TEST_CASE("Collective communications - scatter")
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // The message to send
    std::string const message = "This message is going to come out in separate channels";
    if (message.size() < (unsigned)size) return;

    // How many characters each process gets
    int N = message.size() / size;

    // The receive buffer
    char buffer[256];

    // Do the scatter operation

    // Check the result
    CHECK(message.substr(rank*N, N) == std::string(buffer, N));
}
