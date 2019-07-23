#
# CMakeLists.txt - CMake configuration file for epanet-solver/src
#
# Created: July 2, 2019
# Updated: July 8, 2019
#
# Modified by: Michael E. Tryby
#              US EPA ORD/NRMRL
#


# Sets for output directory for executables and libraries.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


# TODO: Best practices discourage setting variables directly
IF (APPLE)
  set(INSTALL_NAME_DIR @executable_path/../lib)
  set(CMAKE_MACOSX_RPATH 1)
ENDIF (APPLE)

IF (MSVC)
  set(CMAKE_C_FLAGS_RELEASE "/GL")
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
ENDIF (MSVC)



set(HEADER_PATH
    "${PROJECT_SOURCE_DIR}/include"
    )
set(EPANET_PUBLIC_HEADERS
    ${HEADER_PATH}/epanet2_2.h
    ${HEADER_PATH}/epanet2_enums.h
    )

set(EPANET_PRIVATE_HEADERS
    enumstxt.h
    funcs.h
    hash.h
    mempool.h
    text.h
    types.h
    )

set(EPANET_SOURCES
    epanet.c
    epanet2.c
    errors.dat
    genmmd.c
    hash.c
    hash.h
    hydcoeffs.c
    hydraul.c
    hydsolver.c
    hydstatus.c
    inpfile.c
    input1.c
    input2.c
    input3.c
    mempool.c
    output.c
    project.c
    quality.c
    qualreact.c
    qualroute.c
    report.c
    rules.c
    smatrix.c
    )

# configure file groups
source_group("Library"
    FILES
        ${EPANET_PRIVATE_HEADERS}
        ${EPANET_SOURCES}
    )


# create build target for epanet library with python API
if(BUILD_PY_LIB)

  # exclude legacy epanet 2.0 API and include epanet py API
  list(REMOVE_ITEM EPANET_SRC "epanet2.c")
  add_library(epanet_py
    SHARED
        ${EPANET_PRIVATE_HEADERS}
        ${EPANET_SOURCES}
        epanet_py.c
        util/errormanager.c
    )

  include(GenerateExportHeader)
  GENERATE_EXPORT_HEADER(epanet_py
    BASE_NAME epanet_py
    EXPORT_MACRO_NAME EXPORT_PY_API
    EXPORT_FILE_NAME epanet_py_export.h
    STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)

  file(COPY ${CMAKE_CURRENT_BINARY_DIR}/epanet_py_export.h
    DESTINATION ${CURRENT_SOURCE_DIR}/include)

# create build target for code coverage
elseif(BUILD_COVERAGE)

  include(CodeCoverage)
  set(CMAKE_BUILD_TYPE "Debug")
  APPEND_COVERAGE_COMPILER_FLAGS()
  set(CMAKE_C_FLAGS_DEBUG "-O0")

  add_library(epanet2
    SHARED
        ${EPANET_PRIVATE_HEADERS}
        ${EPANET_SOURCES}
    )

# create build target for default epanet library with 2.0 and 2.2 API
else()

  # Build modern 64 bit version of the library
  if("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)" OR NOT MSVC)
    add_library(epanet2
        SHARED
            ${EPANET_PRIVATE_HEADERS}
            ${EPANET_SOURCES}
        )

  # Build legacy 32 bit version of the library with def file interface
  else()
    add_library(epanet2
        SHARED
            ${EPANET_PRIVATE_HEADERS}
            ${EPANET_SOURCES}
            ${PROJECT_SOURCE_DIR}/include/epanet2.def
        )
    set_source_files_properties(${PROJECT_SOURCE_DIR}/include/epanet2.def
        PROPERTIES_HEADER_FILE_ONLY TRUE
        )

  endif()
endif()

target_include_directories(epanet2
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${INCLUDE_DIST}>
    )


install(TARGETS epanet2
    EXPORT epanet2Targets
    RUNTIME    DESTINATION "${TOOL_DIST}"    COMPONENT bin
    LIBRARY    DESTINATION "${TOOL_DIST}"    COMPONENT shlib
    ARCHIVE    DESTINATION "${LIBRARY_DIST}"
    FRAMEWORK  DESTINATION "${TOOL_DIST}"
    )

# Need to list files out individually otherwise is won't work
install(
    FILES
        "${PROJECT_SOURCE_DIR}/include/epanet2.def"
        "${PROJECT_SOURCE_DIR}/include/epanet2.h"
        "${PROJECT_SOURCE_DIR}/include/epanet2_2.h"
        "${PROJECT_SOURCE_DIR}/include/epanet2_enums.h"
    DESTINATION
        "${INCLUDE_DIST}"
    )
