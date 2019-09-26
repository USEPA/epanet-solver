::
::  make.cmd - builds epanet
::
::  Date Created: 9/18/2019
::  Date Updated:
::
::  Author: Michael E. Tryby
::          US EPA - ORD/NRMRL
::
::  Requires:
::    Build Tools for Visual Studio download:
::      https://visualstudio.microsoft.com/downloads/
::
::    CMake download:
::      https://cmake.org/download/
::
::  Environment Variables:
::    BUILD_HOME - defaults to build
::
::  Optional Arguments:
::    1 - ("GENERATOR") defaults to "Visual Studio 15 2017"
::

::echo off
setlocal EnableDelayedExpansion


echo INFO: Building epanet  ...

set "BUILD_HOME=build"


:: determine project directory
set "CUR_DIR=%CD%"
set "SCRIPT_HOME=%~dp0"
cd %SCRIPT_HOME%
cd ..

:: check for requirements
where cmake > nul
if %ERRORLEVEL% NEQ 0 ( echo "ERROR: cmake not installed" & exit /B 1 )


:: process args
if [%1]==[] ( set "GENERATOR=Visual Studio 15 2017"
) else ( set "GENERATOR=%~1" )


:: if generator has changed delete the build folder
if exist %BUILD_HOME% (
  for /F "tokens=*" %%f in ( 'findstr CMAKE_GENERATOR:INTERNAL %BUILD_HOME%\CmakeCache.txt' ) do (
    for /F "delims=:= tokens=3" %%m in ( 'echo %%f' ) do (
      set CACHE_GEN=%%m
      if not "!CACHE_GEN!" == "!GENERATOR!" ( rmdir /s /q %BUILD_HOME% & mkdir %BUILD_HOME% )
    )
  )
) else ( mkdir %BUILD_HOME% )

cd %BUILD_HOME%
cmake -G"%GENERATOR%" -DBUILD_TESTS=OFF ..

:: perform build
cmake --build . --config Release --target package

move epanet-solver*.zip %PROJECT_PATH%


:: return to users current dir
cd %CUR_DIR%
