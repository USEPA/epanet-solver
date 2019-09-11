<!---
   Testing.md

   Created: Sept 10, 2019
   Updated:

   Author: Michael E. Tryby
           US EPA - ORD/NRMRL
--->


## Unit testing

**Requirements**
CTest, and Boost


CTest is part of the CMake build system and has many capabilities. In this project it is used as a test runner. When adding new unit tests they need to be registed with CTest before they will automatically run. Tests can be registered using the `add_test()` command in `tests\CMakeLists.txt`.

With the exception of the reentrancy test, all unit tests are written using Boost Test framework. It provides all the standard unit test idioms like, grouping tests into suites, test fixtures, custom comparators, and much more. Becoming familiar with the patterns found in the unit tests that have already been written is an efficient way to learn how to write and add new ones.

Follow the link for more information about [Boost Test](https://www.boost.org/doc/libs/1_67_0/libs/test/doc/html/index.html).


### Guidelines

 1. To help minimize build time, add tests to existing test suites rather than creating separate test executables. Individual files already exist for each category of functions found in the epanet-solver library. At build time they get linked together into a single test executable.

 2. The `BOOST_REQUIRE` macro causes the code to exit immediately when an error is detected. This can cause memory leaks and other spurious runtime issues. When adding new tests, the `BOOST_CHECK` macro is preferred.

 3. Unit Tests are written to the C++11 Standard.
