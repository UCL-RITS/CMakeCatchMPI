/*=============================================================================

  CMAKECATCHMPI: A software package to demo MPI with CMake, CTest and Catch.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef ccmpiExceptionMacro_h
#define ccmpiExceptionMacro_h

#include "ccmpiException.h"

#define ccmpiExceptionThrow() throw ccmpi::Exception(__FILE__,__LINE__)

#endif
