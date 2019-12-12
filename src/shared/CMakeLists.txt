#
# CMakeLists.txt - CMake configuration file for epanet/src/shared
#
# Date Created: 9/17/2019
#
# Author: Michael E. Tryby
#         US EPA - ORD/NRMRL
#


set(SHARED_SOURCES
    cstr_helper.c
    errormanager.c
    filemanager.c
    )

set(SHARED_HEADERS
    cstr_helper.h
    errormanager.h
    filemanager.h
    )

add_library(shared_objs OBJECT ${SHARED_SOURCES})
