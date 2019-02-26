/*=============================================================================

  CMAKECATCHMPI: A software package to demo MPI with CMake, CTest and Catch.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef ccmpiWin32ExportHeader_h
#define ccmpiWin32ExportHeader_h

/**
* \file ccmpiWin32ExportHeader.h
* \brief Header to sort Windows dllexport/dllimport.
*/

#if (defined(_WIN32) || defined(WIN32)) && !defined(CMAKECATCHMPI_STATIC)
  #ifdef CMAKECATCHMPI_WINDOWS_EXPORT
    #define CMAKECATCHMPI_WINEXPORT __declspec(dllexport)
  #else
    #define CMAKECATCHMPI_WINEXPORT __declspec(dllimport)
  #endif  /* CMAKECATCHMPI_WINEXPORT */
#else
/* linux/mac needs nothing */
  #define CMAKECATCHMPI_WINEXPORT
#endif

#endif
