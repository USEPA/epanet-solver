::
::  before-test.cmd - Stages test and benchmark files for epanet nrtest
::
::  Date Created: 4/3/2018
::  Date Updated: 9/3/2019
::
::  Author: Michael E. Tryby
::          US EPA - ORD/NRMRL
::
::  Dependencies:
::    curl
::    7z
::
::  Environment Variables:
::    BUILD_HOME - relative path
::    TEST_HOME  - relative path
::
::  Arguments:
::    None
::
::  Note:
::    Tests and benchmark files are stored in the epanet-nrtests repo.
::    This script retrieves them using a stable URL associated with a GitHub
::    release stages the files and sets up the environment for nrtest to run.
::

::@echo off
EnableDelayedExpansion

set "SCRIPT_HOME=%~dp0"
cd %SCRIPT_HOME%
pushd ..
set PROJ_DIR=%CD%

set "EPANET_NRTESTS_URL=https://github.com/michaeltryby/epanet-nrtests"

:: check for dependencies
WHERE curl
IF %ERRORLEVEL% NEQ 0 ECHO curl not installed & EXIT /B 1
WHERE 7z
IF %ERRORLEVEL% NEQ 0 ECHO 7zip not installed & EXIT /B 1


:: check BUILD_HOME and TEST_HOME and apply defaults
if not defined BUILD_HOME ( set "BUILD_HOME=buildprod" )
if not defined TEST_HOME ( set "TEST_HOME=nrtestsuite" )


:: determine platform from CMakeCache.txt if not already defined
if [%PLATFORM%]==[] (
  for /F "tokens=*" %%p in ( 'findstr CMAKE_SHARED_LINKER_FLAGS:STRING %BUILD_HOME%\CmakeCache.txt' ) do ( set "FLAG=%%p" )
  if "%FLAG:~-3%" == "X86" ( set "PLATFORM=win32" ) else ( set "PLATFORM=win64" )
)
if not defined PLATFORM ( echo "ERROR: PLATFORM could not be determined" & exit /B 1 )



echo INFO: Staging files for regression testing


:: hack to determine latest tag in epanet-example-networks repo
set "LATEST_URL=%EPANET_NRTESTS_URL%/releases/latest"
for /F delims^=^"^ tokens^=2 %%g in ('curl --silent %LATEST_URL%') do ( set "LATEST_TAG=%%~nxg" )

if defined LATEST_TAG (
  set "TESTFILES_URL=%EPANET_NRTESTS_URL%/archive/%LATEST_TAG%.zip"
  set "BENCHFILES_URL=%EPANET_NRTESTS_URL%/releases/download/%LATEST_TAG%/benchmark-%PLATFORM%.zip"
) else ( echo ERROR: Unable to determine latest tag & exit /B 1 )

:: create a clean directory for staging regression tests
if exist %TEST_HOME% (
  rmdir /s /q %TEST_HOME%
)
mkdir  %TEST_HOME%
cd  %TEST_HOME%


:: retrieve nrtest cases for regression testing
curl -fsSL -o nrtestfiles.zip %TESTFILES_URL%

:: retrieve epanet benchmark results
curl -fsSL -o benchmark.zip %BENCHFILES_URL%


:: extract tests, scripts, benchmarks, and manifest
7z x nrtestfiles.zip * > nul
7z x benchmark.zip -obenchmark\ > nul
7z e benchmark.zip -o. manifest.json -r > nul


:: determine REF_BUILD_ID from manifest if not already defined
if [%REF_BUILD_ID%] == [] (
  for /F "tokens=*" %%d in ( 'findstr %PLATFORM% manifest.json' ) do (
    set "D=%%d"
    set REF_BUILD_ID=%D:~22,-2%
  )
)
if not defined REF_BUILD_ID ( echo "ERROR: REF_BUILD_ID could not be determined" & exit /B 1 )


:: set up symlinks for tests directory
mklink /D .\tests .\epanet-nrtests-%LATEST_TAG:~1%\public > nul

:: return to project home
cd ..
