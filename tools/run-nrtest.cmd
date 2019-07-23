::
::  run_nrtest.cmd - Runs numerical regression test
::
::  Date Created: 1/8/2018
::  Date Updated: 7/18/2019
::
::  Author: Michael E. Tryby
::          US EPA - ORD/NRMRL
::
::  Dependencies:
::    python -m pip install -r requirements.txt
::
::  Environment Variables:
::    BUILD_HOME - relative path
::    TEST_HOME  - relative path
::    PLATFORM
::    REF_BUILD_ID
::
::  Arguments:
::    1 - (SUT_VERSION)  - optional argument
::    2 - (SUT_BUILD_ID) - optional argument
::

::@echo off
setlocal EnableDelayedExpansion

:: determine project directory
set "SCRIPT_HOME=%~dp0"
cd %SCRIPT_HOME%
pushd ..
set PROJ_DIR=%CD%
popd

cd %PROJ_DIR%\%TEST_HOME%

:: Check existence

if [%1]==[] (set "SUT_VERSION=unknown"
) else ( set "SUT_VERSION=%~1" )

if [%2]==[] ( set "SUT_BUILD_ID=local"
) else ( set "SUT_BUILD_ID=%~2" )


:: check if app config file exists
if not exist apps\epanet-%SUT_BUILD_ID%.json (
  mkdir apps
  call %SCRIPT_HOME%\app-config.cmd %PROJ_DIR%\%BUILD_HOME%\bin\Release^
    %PLATFORM% %SUT_BUILD_ID% %SUT_VERSION% > apps\epanet-%SUT_BUILD_ID%.json
)


:: build test list
set TESTS=
for /F "tokens=*" %%T in ('dir /b tests') do ( set "TESTS=!TESTS! tests\%%T" )


:: determine location of python Scripts folder
for /F "tokens=*" %%G in ('where python') do (
  set PYTHON_DIR=%%~dpG
  goto break_loop_1
)
:break_loop_1
set "NRTEST_SCRIPT_PATH=%PYTHON_DIR%Scripts"


:: build nrtest execute command
set NRTEST_EXECUTE_CMD=python %NRTEST_SCRIPT_PATH%\nrtest execute
set TEST_APP_PATH=apps\epanet-%SUT_BUILD_ID%.json
set TEST_OUTPUT_PATH=benchmark\epanet-%SUT_BUILD_ID%

:: build nrtest compare command
set NRTEST_COMPARE_CMD=python %NRTEST_SCRIPT_PATH%\nrtest compare
set REF_OUTPUT_PATH=benchmark\epanet-%REF_BUILD_ID%
set RTOL_VALUE=0.01
set ATOL_VALUE=0.0

:: change current directory to test suite
::cd %TEST_HOME%

:: if present clean test benchmark results
if exist %TEST_OUTPUT_PATH% (
  rmdir /s /q %TEST_OUTPUT_PATH%
)

:: perform nrtest execute
echo INFO: Creating SUT %SUT_BUILD_ID% artifacts
set NRTEST_COMMAND=%NRTEST_EXECUTE_CMD% %TEST_APP_PATH% %TESTS% -o %TEST_OUTPUT_PATH%
:: if there is an error exit the script with error value 1
%NRTEST_COMMAND% || exit /B 1

echo.

:: perform nrtest compare
echo INFO: Comparing SUT artifacts to REF %REF_BUILD_ID%
set NRTEST_COMMAND=%NRTEST_COMPARE_CMD% %TEST_OUTPUT_PATH% %REF_OUTPUT_PATH% --rtol %RTOL_VALUE% --atol %ATOL_VALUE% -o benchmark\receipt.json
%NRTEST_COMMAND%
