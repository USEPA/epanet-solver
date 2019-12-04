#
# CMakeLists.txt - CMake configuration file for epanet/tests
#
# Date Created: 9/17/2019
#
# Author: Michael E. Tryby
#         US EPA - ORD/NRMRL
#

#Prep ourselves for compiling with boost
if(WIN32)
    set(Boost_USE_STATIC_LIBS       ON)
else()
    set(Boost_USE_STATIC_LIBS       OFF)
    add_definitions(-DBOOST_ALL_DYN_LINK)
endif()

find_package(Boost COMPONENTS unit_test_framework system thread filesystem)
include_directories (${Boost_INCLUDE_DIRS})


add_subdirectory(outfile)
add_subdirectory(shared)
add_subdirectory(solver)


# TODO: Bad practice should set specific target compile features instead
if(UNIX)
    set(CMAKE_CXX_FLAGS
        "-std=c++11"
        )
endif(UNIX)


add_executable(test_net_builder
    test_net_builder.cpp
    )
target_link_libraries(test_net_builder
    ${Boost_LIBRARIES}
    epanet2
    )


add_executable(test_reent
    test_reent.cpp
    )
if(MSVC)
    target_link_libraries(test_reent
        ${Boost_LIBRARIES}
        epanet2
        )
else()
    target_link_libraries(test_reent
        ${Boost_LIBRARIES}
        pthread
        epanet2
        )
endif()


set_target_properties(test_net_builder test_reent
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )


# Setting up tests to run from build tree
set(TEST_BIN_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIGURATION>")

add_test(NAME test_toolkit
    COMMAND "${TEST_BIN_DIRECTORY}/test_toolkit"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/solver/data
    )

add_test(NAME test_net_builder
    COMMAND "${TEST_BIN_DIRECTORY}/test_net_builder"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data
    )

add_test(NAME test_reent
    COMMAND "${TEST_BIN_DIRECTORY}/test_reent"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data
    )


# ctest doesn't like tests added in subdirectories so adding them here
add_test(NAME test_cstrhelper
    COMMAND "${TEST_BIN_DIRECTORY}/test_cstrhelper"
    )

add_test(NAME test_errormanager
    COMMAND "${TEST_BIN_DIRECTORY}/test_errormanager"
    )

add_test(NAME test_filemanager
    COMMAND "${TEST_BIN_DIRECTORY}/test_filemanager"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outfile/data
    )

add_test(NAME test_output
    COMMAND "${TEST_BIN_DIRECTORY}/test_output"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outfile/data
    )
