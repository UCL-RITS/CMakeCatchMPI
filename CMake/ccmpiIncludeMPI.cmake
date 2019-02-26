#/*============================================================================
#
#  CMAKECATCHMPI: A software package to demo MPI with CMake, CTest and Catch.
#
#  Copyright (c) University College London (UCL). All rights reserved.
#
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
#  See LICENSE.txt in the top level directory for details.
#
#============================================================================*/

if(CMAKECATCHMPI_USE_MPI)
  find_package(MPI REQUIRED)
  message("Found MPI, with mpiexec=${MPIEXEC}")

  # Assume, for the purpose of this example project, that we are doing c++.
  # If you fork this project, you should set the variables in your chosen language.
  include_directories(${MPI_CXX_INCLUDE_PATH})
  set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} ${MPI_CXX_COMPILE_FLAGS} ")
  set(CMAKE_EXE_LINKER_FLAGS " ${CMAKE_EXE_LINKER_FLAGS} ${MPI_CXX_LINK_FLAGS} ")
  list(APPEND ALL_THIRD_PARTY_LIBRARIES ${MPI_CXX_LIBRARIES})

  message("Adding MPI include:${MPI_CXX_INCLUDE_PATH}.")
  message("Adding MPI libs:${MPI_CXX_LIBRARIES}.")

endif()
