#
# CMakeLists.txt - CMake configuration file for epanet-solver
#
# Requirements:
#   CMake - https://cmake.org/download/
#
# Build Options:
#   BUILD_TESTING  = ON/OFF
#   BUILD_DOCS     = ON/OFF
#   BUILD_PY_LIB   = ON/OFF
#   BUILD_COVERAGE = ON/OFF
#
# Targets:
#   ALL_BUILD  - Builds all targets
#   ZERO_CHECK - Reruns cmake
#   RUN_TESTS  - Builds and runs tests
#   INSTALL    - Stages build artifacts in install dir
#   PACKAGE    - Creates install package (zip file)
#   doxygen    - Builds toolkit docs
#   clean
#
# Generic Invocation:
#   cmake -E make_directory buildprod
#   cmake -G"Visual Studio 15 2017" ./buildprod
#   cmake --build ./buildprod --config Release --target some_target
#
# More information:
#   cmake docs - https://cmake.org/documentation
#


cmake_minimum_required (VERSION 3.13)

if("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    message(FATAL_ERROR "In-source builds are disabled.")
endif()


project(epanet-solver
    VERSION 2.2.0
    )


# Append local dir to module search path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Sets the position independent code property for all targets
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)


# Searches for and create install rules for vcruntime.dll, msvcp.dll, etc.
include(InstallRequiredSystemLibraries)

# Sets default install prefix when cmakecache is initialized for first time
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "..." FORCE)
endif()

# Define install locations (will be prepended by install prefix)
set(TOOL_DIST "bin")
set(INCLUDE_DIST "include")
set(LIBRARY_DIST "lib")
set(CONFIG_DIST  "cmake")


option(BUILD_TESTS "Build component tests (requires Boost)" OFF)
option(BUILD_DOCS "Build toolkit docs (requires Doxygen)" OFF)
option(BUILD_PY_LIB "Build library for Python wrapper" OFF)
option(BUILD_COVERAGE "Build library for coverage" OFF)


add_subdirectory(bindings)

if(BUILD_DOCS)
  add_subdirectory(doc)
endif()

if(NOT BUILD_PY_LIB)
  add_subdirectory(run)
endif()

add_subdirectory(src)
add_subdirectory(src/util)
add_subdirectory(src/outfile)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()


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
