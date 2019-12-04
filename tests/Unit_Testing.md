<!---
   Unit_Testing.md

   Created: Sept 10, 2019
   Updated: Dec 4, 2019

   Author: Michael E. Tryby
           US EPA - ORD/CESER
--->


## Unit Testing EPANET locally on Windows

### Dependencies

Before the project can be built and tested the required dependencies must be installed.

**Summary of Build Dependencies: Windows**

  - Build
      - Build Tools for Visual Studio 2017
      - CMake 3.13

  - Unit Test
      - Boost 1.67.0 (installed in default location "C:\\local")



### Build and Unit Test

EPANET can be built and unit tests run with one simple command.
```
\> cd epanet
\epanet>scripts\make.cmd /t
```


### More Information
See [Wiki/Testing System](https://github.com/USEPA/epanet-solver/wiki/Testing-System)
