::
::  make.cmd - builds epanet
::
:: Requires:
::    Build Tools for Visual Studio download:
::      https://visualstudio.microsoft.com/downloads/
::
::    CMake download:
::      https://cmake.org/download/
::
:: Optional Arguments:
::    1 - ("GENERATOR") defaults to "Visual Studio 15 2017"
::
::
:: Note:
::    This script must be located at the root of the project folder
::    in order to work properly.
::

::echo off
echo INFO: Building epanet  ...

set "BUILD_HOME=build"


:: Determine project path and strip trailing \ from path
set "PROJECT_PATH=%~dp0"
if %PROJECT_PATH:~-1%==\ ( set "PROJECT_PATH=%PROJECT_PATH:~0,-1%" )


:: check for requirements
where cmake > nul
if %ERRORLEVEL% NEQ 0 echo cmake not installed & exit /B 1


:: Process optional arguments
if [%1]==[] ( set "GENERATOR=Visual Studio 15 2017"
) else ( set "GENERATOR=%~1" )


:: if generator has changed delete the build folder
if exist BUILD_HOME (
  for /F "tokens=*" %%f in ( 'findstr CMAKE_GENERATOR:INTERNAL %BUILD_HOME%\CmakeCache.txt' ) do (
    for /F "delims=:= tokens=3" %%m in ( 'echo %%f' ) do (
      if "%%m" NEQ "%GENERATOR%" ( rmdir /s /q %BUILD_HOME% & mkdir %BUILD_HOME% )
    )
  )
) else ( mkdir %BUILD_HOME% )

cd %BUILD_HOME%
cmake -G"%GENERATOR%" -DBUILD_TESTS=OFF ..

:: perform build
cmake --build . --config Release --target package

move epanet-solver*.zip %PROJECT_PATH%


:: return to project root
cd %PROJECT_PATH%
