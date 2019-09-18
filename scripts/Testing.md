<!---
   Testing.md

   Created: Sept 4, 2019
   Updated: Sept 5, 2019

   Author: Michael E. Tryby
           US EPA - ORD/NRMRL
--->

## Regression Testing EPANET locally on Windows


### Dependencies

Before the project can be built and tested the required dependencies must be installed.

**Summary of Build Dependencies: Windows**

  - Build and Test
      - Build Tools for Visual Studio 2017
      - CMake 3.13

  - Regression Test
      - Python 3.6 64 bit
      - curl
      - 7z

Once Python is installed, the following command installs the required packages for regression testing.
```
\> cd epanet
\epanet>pip install -r scripts\requirements-appveyor.txt
```


### Build

EPANET can be built with one simple command.
```
\epanet>scripts\make.cmd
```


### Regression Test

This command runs regression tests for the local build and compares them to the latest benchmark.
```
\epanet>scripts\before-nrtest.cmd && scripts\run-nrtest.cmd
```
