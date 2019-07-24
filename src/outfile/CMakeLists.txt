#
# CMakeLists.txt - CMake configuration file for epanet-output library
#
# Created: March 9, 2018
# Author: Michael E. Tryby
#         US EPA ORD/NRMRL
#


# Sets for output directory for executables and libraries.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(EPANET_OUT_PUBLIC_HEADERS
    include/epanet_output.h
    include/epanet_output_enums.h
    include/epanet_output_export.h
    )


# the binary output file API
add_library(epanet-output
    SHARED
        src/epanet_output.c
        $<TARGET_OBJECTS:util_objs>
    )

target_compile_options(epanet-output
    PUBLIC
        "$<$<CXX_COMPILER_ID:MSVC>:"
            "/MT$<$<CONFIG:Debug>:d>"
        ">"
    )

target_include_directories(epanet-output
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${INCLUDE_DIST}>
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/
    )


include(GenerateExportHeader)
generate_export_header(epanet-output
  BASE_NAME epanet_output
  EXPORT_MACRO_NAME EXPORT_OUT_API
  EXPORT_FILE_NAME epanet_output_export.h
  STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)

file(COPY ${CMAKE_CURRENT_BINARY_DIR}/epanet_output_export.h DESTINATION
  ${CMAKE_CURRENT_SOURCE_DIR}/include)



install(TARGETS epanet-output EXPORT epanet-outputTargets
    RUNTIME    DESTINATION "${TOOL_DIST}"
    LIBRARY    DESTINATION "${TOOL_DIST}"
    ARCHIVE    DESTINATION "${LIBRARY_DIST}"
    FRAMEWORK  DESTINATION "${TOOL_DIST}"
    )

install(FILES ${EPANET_OUT_PUBLIC_HEADERS} DESTINATION "${INCLUDE_DIST}")
