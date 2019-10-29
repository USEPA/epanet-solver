::
::  gen-config.cmd - Generated nrtest app configuration file for test executable
::
::  Date Created: 1/8/2018
::  Date Updated: 10/29/2019
::
::  Author: Michael E. Tryby
::          US EPA - ORD/NRMRL
::
::  Dependencies:
::    git
::
::  Environment Variables:
::    PROJECT
::    BUILD_HOME - defaults to "build"
::    PLATFORM
::
::  Arguments:
::    1 - absolute path to test executable (valid path seperator for nrtest is "/")
::    2 - (platform)
::    3 - (build identifier for SUT)
::

@echo off
setlocal

:: check that dependencies are installed
where git > nul
if %ERRORLEVEL% neq 0 ( echo "ERROR: git not installed" & exit /B 1 )


:: epanet target created by the cmake build script
set TEST_CMD=runepanet.exe

:: remove quotes from path and convert backward to forward slash
set ABS_BUILD_PATH=%~1
set ABS_BUILD_PATH=%ABS_BUILD_PATH:\=/%


:: process arguments
IF [%2]==[] ( set "PLATFORM=unknown"
) ELSE ( set "PLATFORM=%~2" )

IF [%3]==[] ( set "BUILD_ID=unknown"
) ELSE ( set "BUILD_ID=%~3" )


:: determine version
for /F "tokens=1" %%v in ( 'git rev-parse --short HEAD' ) do ( set "VERSION=%%v" )


echo {
echo     "name" : "epanet",
echo     "version" : "%VERSION%",
echo     "description" : "%PLATFORM% %BUILD_ID%",
echo     "setup_script" : "",
echo     "exe" : "%ABS_BUILD_PATH%/%TEST_CMD%"
echo }
