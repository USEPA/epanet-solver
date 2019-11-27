#
# CMakeLists.txt - CMake configuration file for tests/solver
#
# Date Created: 9/17/2019
#
# Author: Michael E. Tryby
#         US EPA - ORD/NRMRL
#

set(toolkit_test_srcs
    test_toolkit.cpp
    test_project.cpp
    test_hydraulics.cpp
    test_quality.cpp
    test_report.cpp
    test_analysis.cpp
    test_node.cpp
    test_demand.cpp
    test_link.cpp
#    test_pump.cpp
    test_pattern.cpp
    test_curve.cpp
    test_control.cpp
    # ADD NEW TESTS TO EXISTING TESTS SUITES
    )

add_executable(test_toolkit
    ${toolkit_test_srcs}
    )

target_link_libraries(test_toolkit
    ${Boost_LIBRARIES}
    epanet2
    )

set_target_properties(test_toolkit
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
