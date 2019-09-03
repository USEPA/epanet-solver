## Testing EPANET locally on Windows


### Dependencies

  - Build and Test
    - CMake 3.13
    - Build Tools for Visual Studio 2017
    - Boost 1.67

  - Regression Test
    - curl
    - 7z
    - Python 3

```
\>pip install -r tools\requirements-appveyor.txt
```


### Build and Test

```
\>ctest --build-and-test .\ .\buildprod --build-generator "Visual Studio 15 2017" --build-config Release --build-options -DBUILD_TESTS=ON -DBOOST_ROOT=C:\local\boost_1_67_0 --test-command ctest -C Release
```


### Regression Test

```
\>tools\before-test.cmd
\>tools\run-nrtest.cmd
```
