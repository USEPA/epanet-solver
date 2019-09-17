#
# CMakeLists.txt - CMake configuration file for epanet/shared
#


set(SHARED_SOURCES
    cstr_helper.c
    errormanager.c
    filemanager.c
    list.c
    )

set(SHARED_HEADERS
    cstr_helper.h
    errormanager.h
    filemanager.h
    list.h
    )

add_library(shared_objs OBJECT ${SHARED_SOURCES})

target_include_directories(shared_objs
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
