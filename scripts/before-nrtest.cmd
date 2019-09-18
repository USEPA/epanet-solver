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
::    1 - (RELEASE_TAG) release tag for benchmark version (defaults to latest tag)
::
::  Note:
::    Tests and benchmark files are stored in the epanet-nrtests repo.
::    This script retrieves them using a stable URL associated with a GitHub
::    release, stages the files, and sets up the environment for nrtest to run.
::

::@echo off


:: check that dependencies are installed
where curl > nul
if %ERRORLEVEL% neq 0 ( echo curl not installed & exit /B 1 )
where 7z > nul
if %ERRORLEVEL% neq 0 ( echo 7zip not installed & exit /B 1 )


:: determine project directory
set "SCRIPT_HOME=%~dp0"
cd %SCRIPT_HOME%
pushd ..
set PROJ_DIR=%CD%


:: set URL to github repo with test files
set "EPANET_NRTESTS_URL=https://github.com/michaeltryby/epanet-nrtests"

:: if release tag isn't provided latest tag will be retrieved
if [%1] == [] (set "RELEASE_TAG="
) else (set "RELEASE_TAG=%~1")


:: check BUILD_HOME and TEST_HOME and apply defaults
if not defined BUILD_HOME ( set "BUILD_HOME=buildprod" )
if not defined TEST_HOME ( set "TEST_HOME=nrtestsuite" )


:: if not already defined determine platform from CmakeCache.txt file
if [%PLATFORM%]==[] (
  for /F "tokens=*" %%f in ( 'findstr CMAKE_SHARED_LINKER_FLAGS:STRING %BUILD_HOME%\CmakeCache.txt' ) do (
    for /F "delims=: tokens=3" %%m in ( 'echo %%f' ) do (
      if "%%m" == "X86" ( set "PLATFORM=win32" ) else if "%%m" == "x64" ( set "PLATFORM=win64" )
    )
  )
)
if not defined PLATFORM ( echo "ERROR: PLATFORM could not be determined" & exit /B 1 )



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
cd %TEST_HOME%


:: retrieve nrtest cases and benchmark results for regression testing
curl -fsSL -o nrtestfiles.zip %TESTFILES_URL%
curl -fsSL -o benchmark.zip %BENCHFILES_URL%


:: extract tests, scripts, benchmarks, and manifest
7z x nrtestfiles.zip * > nul
7z x benchmark.zip -obenchmark\ > nul
7z e benchmark.zip -o. manifest.json -r > nul


:: determine REF_BUILD_ID from manifest file
for /F delims^=^"^ tokens^=4 %%d in ( 'findstr %PLATFORM% manifest.json' ) do (
  for /F "tokens=2" %%r in ( 'echo %%d' ) do ( set "REF_BUILD_ID=%%r" )
)
if not defined REF_BUILD_ID ( echo "ERROR: REF_BUILD_ID could not be determined" & exit /B 1 )


:: set up symlinks for tests directory
mklink /D .\tests .\epanet-nrtests-%RELEASE_TAG:~1%\public > nul

:: return to project home
cd ..
