/*=============================================================================

  CMAKECATCHMPI: A software package to demo MPI with CMake, CTest and Catch.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "ccmpiMyFunctions.h"
#include "ccmpiExceptionMacro.h"

#include <cassert>
#include <iostream>

#include <mpi.h>

/**
 * \brief Command Line Entry Point for end-user MPI program.
 */
int main(int argc, char** argv)
{
  int returnStatus = EXIT_FAILURE;

  // Must be first MPI call
  MPI_Init(&argc, &argv);

  try
  {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Blocking send, from 0 to 1
    std::string peace = "I come in peace!";
    if (rank == 0) {
       int const error = MPI_Send(
         (void*) peace.c_str(), peace.size() + 1, MPI_CHAR, 1, 42, MPI_COMM_WORLD);
       // We do not guarantee that Rank 1 has received the message yet
       // But nor do we necessarily know it hasn't.
       // But we are definitely allowed to change the string, as MPI promises
       // it has been buffered
       peace = "Shoot to kill!"; // Safe to reuse the send buffer.
       assert(error ==  MPI_SUCCESS);
    }
    if (rank == 1) {
        char buffer[256];
        int const error = MPI_Recv(
          buffer, 256, MPI_CHAR, 0, 42, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        assert(error ==  MPI_SUCCESS);
        assert(std::string(buffer) == peace);
    }

    returnStatus = EXIT_SUCCESS;
  }
  catch (ccmpi::Exception& e)
  {
    std::cerr << "Caught ccmpi::Exception: " << e.GetDescription() << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << "Caught std::exception: " << e.what() << std::endl;
  }

  // Must be last MPI call
  MPI_Finalize();

  return returnStatus;
}
