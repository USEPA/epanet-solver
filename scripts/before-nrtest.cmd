::
::  before-test.cmd - Stages test and benchmark files for epanet nrtest
::
::  Date Created: 4/3/2018
::  Date Updated: 10/9/2019
::
::  Author: Michael E. Tryby
::          US EPA - ORD/NRMRL
::
::  Dependencies:
::    curl
::    7z
::
::  Environment Variables:
::    BUILD_HOME - defaults to "build"
::    TEST_HOME  - defaults to "nrtests"
::    PLATFORM
::
::  Arguments:
::    1 - (RELEASE_TAG) release tag for benchmark version (defaults to latest tag)
::
::  Note:
::    Tests and benchmark files are stored in the epanet-nrtests repo.
::    This script retrieves them using a stable URL associated with a GitHub
::    release, stages the files, and sets up the environment for nrtest to run.
::

::@echo off
setlocal

:: check that dependencies are installed
where curl > nul
if %ERRORLEVEL% neq 0 ( echo "ERROR: curl not installed" & exit /B 1 )
where 7z > nul
if %ERRORLEVEL% neq 0 ( echo "ERROR: 7zip not installed" & exit /B 1 )


:: determine project directory
set "CUR_DIR=%CD%"
set "SCRIPT_HOME=%~dp0"
cd %SCRIPT_HOME%
cd ..

:: set URL to github repo with test files
set "EPANET_NRTESTS_URL=https://github.com/michaeltryby/epanet-nrtests"

:: if release tag isn't provided latest tag will be retrieved
if [%1] == [] (set "RELEASE_TAG="
) else (set "RELEASE_TAG=%~1")


:: check BUILD_HOME and TEST_HOME and apply defaults
if not defined BUILD_HOME ( set "BUILD_HOME=build" )
if not defined TEST_HOME ( set "TEST_HOME=nrtests" )
if not defined PLATFORM ( echo "ERROR: PLATFORM must be defined" & exit /B 1 )


echo INFO: Staging files for regression testing


:: determine latest tag in the tests repo
if [%RELEASE_TAG%] == [] (
  for /F delims^=^"^ tokens^=2 %%g in ('curl --silent %EPANET_NRTESTS_URL%/releases/latest') do (
    set "RELEASE_TAG=%%~nxg"
  )
)

if defined RELEASE_TAG (
  set "TESTFILES_URL=%EPANET_NRTESTS_URL%/archive/%RELEASE_TAG%.zip"
  set "BENCHFILES_URL=%EPANET_NRTESTS_URL%/releases/download/%RELEASE_TAG%/benchmark-%PLATFORM%.zip"
) else ( echo ERROR: tag %RELEASE_TAG% is invalid & exit /B 1 )


:: create a clean directory for staging regression tests
if exist %TEST_HOME% (
  rmdir /s /q %TEST_HOME%
)
mkdir %TEST_HOME%
if %ERRORLEVEL% NEQ 0 ( echo "ERROR: unable to make %TEST_HOME% dir" & exit /B 1 )
cd %TEST_HOME%


:: retrieve nrtest cases and benchmark results for regression testing
curl -fsSL -o nrtestfiles.zip %TESTFILES_URL%
curl -fsSL -o benchmark.zip %BENCHFILES_URL%


:: extract tests, scripts, benchmarks, and manifest
7z x nrtestfiles.zip * > nul
7z x benchmark.zip -obenchmark\ > nul
7z e benchmark.zip -o. manifest.json -r > nul


:: set up symlinks for tests directory
mklink /D .\tests .\epanet-nrtests-%RELEASE_TAG:~1%\public > nul


endlocal


:: determine REF_BUILD_ID from manifest file
for /F delims^=^"^ tokens^=4 %%d in ( 'findstr %PLATFORM% %TEST_HOME%\manifest.json' ) do (
  for /F "tokens=2" %%r in ( 'echo %%d' ) do ( set "REF_BUILD_ID=%%r" )
)
if not defined REF_BUILD_ID ( echo "ERROR: REF_BUILD_ID could not be determined" & exit /B 1 )


:: return to users current directory
cd %CUR_DIR%
