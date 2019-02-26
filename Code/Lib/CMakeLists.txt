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

set(CMAKECATCHMPI_LIBRARY_NAME ccmpi)

set(CMAKECATCHMPI_LIBRARY_SRCS
  ccmpiMyFunctions.cpp
  ccmpiException.cpp
)

set(CMAKECATCHMPI_LIBRARY_HDRS
  ccmpiExceptionMacro.h
)

add_library(${CMAKECATCHMPI_LIBRARY_NAME} ${CMAKECATCHMPI_LIBRARY_HDRS} ${CMAKECATCHMPI_LIBRARY_SRCS})

if(BUILD_SHARED_LIBS)
  if(WIN32)
    add_definitions(-DCMAKECATCHMPI_WINDOWS_EXPORT)
  endif(WIN32)
endif(BUILD_SHARED_LIBS)

target_link_libraries(${CMAKECATCHMPI_LIBRARY_NAME} PRIVATE ${ALL_THIRD_PARTY_LIBRARIES})

