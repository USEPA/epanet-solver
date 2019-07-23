::
::  before-test.cmd - Stages test and benchmark files for epanet nrtest
::
::  Date Created: 4/3/2018
::  Date Updated: 8/15/2019
::
::  Author: Michael E. Tryby
::          US EPA - ORD/NRMRL
::
::  Dependencies:
::    curl
::    7z
::
::  Environment Variables:
::    BUILD_HOME
::    TEST_HOME
::    PLATFORM
::
::  Arguments:
::    1 - REF_BUILD_ID - required argument
::
::  Note:
::    Tests and benchmark files are stored in the epanet-nrtests repo.
::    This script retrieves them using a stable URL associated with a GitHub
::    release stages the files and sets up the environment for nrtest to run.
::

::@echo off

set "SCRIPT_HOME=%~dp0"
cd %SCRIPT_HOME%
pushd ..
set PROJECT_DIR=%CD%
popd

set "EPANET_NRTESTS_URL=https://github.com/OpenWaterAnalytics/epanet-example-networks"


:: apply defaults for BUILD_HOME and TEST_HOME if not already defined
if not defined BUILD_HOME ( set "BUILD_HOME=%PROJECT_DIR%\buildprod" )
if not defined TEST_HOME ( set "TEST_HOME=%PROJECT_DIR%\nrtestsuite" )

:: determine platform from CMakeCache.txt if not already defined
if not defined PLATFORM (
  for /F "tokens=*" %%p in ( 'findstr CMAKE_SHARED_LINKER_FLAGS:STRING %BUILD_HOME%\CmakeCache.txt' ) do ( set "FLAG=%%p" )
  for /F "delims=: tokens=3" %%m in ( 'echo %FLAG%' ) do if "%%m"=="x64" ( set "PLATFORM=win64" ) else ( set "PLATFORM=win32" )
)

:: set REF_BUILD_ID using argument to script
if [%1]==[] ( echo "ERROR: REF_BUILD_ID must be defined" & exit /B 1
) else (set "REF_BUILD_ID=%~1" )


echo INFO: Staging files for regression testing


:: hack to determine latest tag in epanet-example-networks repo
set "LATEST_URL=%EPANET_NRTESTS_URL%/releases/latest"
for /F delims^=^"^ tokens^=2 %%g in ('curl --silent %LATEST_URL%') do ( set "LATEST_TAG=%%~nxg" )

if defined LATEST_TAG (
  set "TESTFILES_URL=%EPANET_NRTESTS_URL%/archive/%LATEST_TAG%.zip"
  set "BENCHFILES_URL=%EPANET_NRTESTS_URL%/releases/download/%LATEST_TAG%/benchmark-%PLATFORM%-%REF_BUILD_ID%.zip"
) else ( echo ERROR: Unable to determine latest tag & exit /B 1 )

:: create a clean directory for staging regression tests
if exist %TEST_HOME% (
  rmdir /s /q %TEST_HOME%
)
mkdir %TEST_HOME%
cd %TEST_HOME%


:: retrieve nrtest cases for regression testing
curl -fsSL -o nrtestfiles.zip %TESTFILES_URL%

:: retrieve epanet benchmark results
curl -fsSL -o benchmark.zip %BENCHFILES_URL%


:: extract tests, scripts, benchmarks, and manifest
7z x nrtestfiles.zip * > nul
7z x benchmark.zip -obenchmark\ > nul
7z e benchmark.zip -o. manifest.json -r > nul


:: set up symlinks for tests directory
mklink /D .\tests .\epanet-example-networks-%LATEST_TAG:~1%\epanet-tests > nul

:: return to project home
cd %PROJECT_DIR%
