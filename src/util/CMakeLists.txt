#
# CMakeLists.txt - CMake configuration file for targets/util
#
# Created: July 19, 2019
#
# Author: Michael E. Tryby
#         US EPA ORD/NRMRL
#



set(UTIL_SOURCES
    cstr_helper.c
    errormanager.c
    filemanager.c
    list.c
    )

set(UTIL_HEADERS
    cstr_helper.h
    errormanager.h
    filemanager.h
    list.h
    )

add_library(util_objs OBJECT ${UTIL_SOURCES})

target_include_directories(util_objs
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
