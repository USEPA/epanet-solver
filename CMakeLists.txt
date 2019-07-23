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

if("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    message(FATAL_ERROR "In-source builds are disabled.")
endif()


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

add_subdirectory(src)
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
