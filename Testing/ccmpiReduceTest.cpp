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

TEST_CASE("Collective communications - reduce")
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int TERMS_PER_PROCESS = 1000;
    double my_denominator = rank * TERMS_PER_PROCESS * 2 + 1;
    double sign = 1;
    double my_result = 0.0;
    for (int i(0); i<TERMS_PER_PROCESS; ++i)
    {
        my_result += sign / my_denominator;
        my_denominator += 2;
        sign = -sign;
    }

    // Parallel reduction code goes here
    double result;

    // Check result just on root
    if (rank == 0) {
        double abs_err = fabs(result * 4.0 - M_PI);
        CHECK(abs_err < 0.001);
        std::cout << "With " << size << " processes, error = "
                  << abs_err << std::endl;
    }
}
