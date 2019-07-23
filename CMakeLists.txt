# CMakeLists.txt - CMake configuration file for EPANET 2.0
#
# CMake is a cross-platform build tool. CMake generates platform native
# build systems that can be used with your compiler of choice. CMake uses a
# generator concept to represent different build tooling. CMake automatically
# detects the platform it is running on and generates the appropriate makefiles
# for the platform default compiler. Different generators can also be specified.
#
# Note: CMake requires that your platform build system and compiler are
# properly installed. Build using Visual Studio requires msbuild shell.
#
# Build Options:
#   BUILD_TESTS = ON/OFF
#   BUILD_PY_LIB = ON/OFF
#
# Generic Invocation:
#   cmake -E make_directory buildprod
#   cd build
#   cmake -G GENERATOR -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON ..
#   cmake --build . --target SOME_TARGET --config Release
#
# More information:
#   cmake --help
#
#   CMake is available at https://cmake.org/download/
#

cmake_minimum_required (VERSION 3.0)

project(epanet
    VERSION 2.2.0
    )


# Append local dir to module search path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Sets the position independent code property for all targets
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)



# Sets default install prefix when cmakecache is initialized for first time
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "..." FORCE)
endif()

# Define install locations (will be prepended by install prefix)
set(TOOL_DIST "bin")
set(INCLUDE_DIST "include")
set(LIBRARY_DIST "lib")
set(CONFIG_DIST  "cmake")



option(BUILD_TESTS "Build tests (requires Boost)" OFF)
option(BUILD_PY_LIB "Build library for Python wrapper" OFF)
option(BUILD_COVERAGE "Build library for coverage" OFF)


IF (NOT BUILD_PY_LIB)
  add_subdirectory(run)
ENDIF (NOT BUILD_PY_LIB)

add_subdirectory(src/util)
add_subdirectory(src/outfile)

IF (BUILD_TESTS)
    #Prep ourselves for compiling with boost
    IF(WIN32)
        set(Boost_USE_STATIC_LIBS       ON)
    ELSE(TRUE)
        set(Boost_USE_STATIC_LIBS       OFF)
        add_definitions(-DBOOST_ALL_DYN_LINK)
    ENDIF(WIN32)

    find_package(Boost COMPONENTS unit_test_framework system thread filesystem)
    include_directories (${Boost_INCLUDE_DIRS})

    enable_testing()
    add_subdirectory(tests)
    add_subdirectory(tests/outfile)
    add_subdirectory(tests/util)
ENDIF (BUILD_TESTS)


# Sets for output directory for executables and libraries.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)





IF (APPLE)
  set(INSTALL_NAME_DIR @executable_path/../lib)
  set(CMAKE_MACOSX_RPATH 1)
ENDIF (APPLE)

IF (MSVC)
  set(CMAKE_C_FLAGS_RELEASE "/GL")
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
ENDIF (MSVC)


# configure file groups
file(GLOB EPANET_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} src/*.c src/util/*.c)
file(GLOB EPANET_LIB_ALL RELATIVE ${PROJECT_SOURCE_DIR} src/* src/util/*)
# exclude epanet python API from the default build
list(REMOVE_ITEM EPANET_LIB_ALL "src/epanet_py.c")
source_group("Library" FILES ${EPANET_LIB_ALL})


# create build target for epanet library with python API
IF (BUILD_PY_LIB)

  # exclude legacy epanet 2.0 API and include epanet py API
  list(REMOVE_ITEM EPANET_LIB_ALL "src/epanet2.c")
  add_library(epanet_py SHARED ${EPANET_LIB_ALL} src/epanet_py.c src/util/errormanager.c)

  include(GenerateExportHeader)
  GENERATE_EXPORT_HEADER(epanet_py
    BASE_NAME epanet_py
    EXPORT_MACRO_NAME EXPORT_PY_API
    EXPORT_FILE_NAME epanet_py_export.h
    STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)

  file(COPY ${CMAKE_CURRENT_BINARY_DIR}/epanet_py_export.h
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)


# create build target for code coverage
ELSEIF (BUILD_COVERAGE)

include(CodeCoverage)
set(CMAKE_BUILD_TYPE "Debug")
APPEND_COVERAGE_COMPILER_FLAGS()
set(CMAKE_C_FLAGS_DEBUG "-O0")

add_library(epanet2 SHARED ${EPANET_LIB_ALL})


# create build target for default epanet library with 2.0 and 2.2 API
ELSE (BUILD_PY_LIB)

  # the shared library
  IF("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)" OR NOT MSVC)
    add_library(epanet2 SHARED ${EPANET_LIB_ALL})
  ELSE(TRUE)
    add_library(epanet2 SHARED ${EPANET_LIB_ALL} ${PROJECT_SOURCE_DIR}/include/epanet2.def)
    set_source_files_properties(${PROJECT_SOURCE_DIR}/include/epanet2.def PROPERTIES_HEADER_FILE_ONLY TRUE)
  ENDIF("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)" OR NOT MSVC)

ENDIF (BUILD_PY_LIB)

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

install(FILES ${EPANET_PUBLIC_HEADERS} DESTINATION "${INCLUDE_DIST}")



# Install license, authors, releaseNotes
install(
    FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/AUTHORS"
        "${CMAKE_CURRENT_SOURCE_DIR}/ReleaseNotes2_2.md"
    DESTINATION
        "./"
    )

# Create target import scripts so other cmake projects can use epanet libraries
install(
    EXPORT
        epanet2Targets
    DESTINATION
        "${CONFIG_DIST}"
    FILE
        epanet2-config.cmake
    )

install(
    EXPORT
        epanet-outputTargets
    DESTINATION
        "${CONFIG_DIST}"
    FILE
        epanet-output-config.cmake
    )



# Configure CPack driven installer package
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_VENDOR "US_EPA")
set(CPACK_ARCHIVE_FILE_NAME "epanet")


include(CPack)
