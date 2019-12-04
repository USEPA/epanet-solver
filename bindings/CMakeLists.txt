#
# CMakeLists.txt - CMake configuration file for epanet/bindings
#
# Date Created: 9/17/2019
#
# Author: Michael E. Tryby
#         US EPA - ORD/NRMRL
#
# Purpose: Create install target for bindings
#

install(
    FILES
        "epanet2.bas"
        "epanet2.def"
        "epanet2.pas"
        "epanet2.vb"
    DESTINATION
        "bindings"
    )
