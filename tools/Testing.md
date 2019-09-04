## Testing EPANET locally on Windows


### Dependencies

Before the project can be built the required dependencies must be installed.

Summary of Build Dependencies: Windows
  - Build and Test
    - CMake 3.13
    - Build Tools for Visual Studio 2017
    - Boost 1.67

  - Regression Test
    - curl
    - 7z
    - Python 3


The following command installs the Python packages required for regression testing.
```
\>pip install -r tools\requirements-appveyor.txt
```



### Build and Test

EPANET can be built and unit tests run in one composite ctest command.
```
\>ctest --build-and-test .\ .\buildprod --build-generator "Visual Studio 15 2017" --build-config Release --build-options -DBUILD_TESTS=ON -DBOOST_ROOT=C:\local\boost_1_67_0 --test-command ctest -C Release
```


### Regression Test

To run a regression test of the local build against the latest benchmark.
```
\>tools\before-test.cmd && \>tools\run-nrtest.cmd
```
