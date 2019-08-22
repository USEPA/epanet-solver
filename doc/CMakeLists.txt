#
# CMakeLists.txt - CMake configuration file for epanet/doc
#
# Created: August 16, 2019
#
# Author: Michael E. Tryby
#         US EPA ORD/NRMRL
#


find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen not found")
endif()


set(DOXY_SOURCES
    main.dox
    toolkit-usage.dox
    toolkit-examples.dox
    toolkit-files.dox
    input-file.dox
    toolkit-units.dox
    ../include/epanet2_enums.h
    ../include/epanet2_2.h
    modules.dox
    ../src/outfile/include/epanet_output.h
    ../src/outfile/include/epanet_output_enums.h
    output.dox
    )


set(DOXYGEN_PROJECT_NAME "OWA-EPANET Toolkit")
set(DOXYGEN_PROJECT_NUMBER "2.2")
set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C "YES")
set(DOXYGEN_HIDE_SCOPE_NAMES "YES")
set(DOXYGEN_SHOW_INCLUDE_FILES "NO")
set(DOXYGEN_SHOW_USED_FILES  "NO")
set(DOXYGEN_LAYOUT_FILE "DoxygenLayout.xml")
set(DOXYGEN_IMAGE_PATH ".")
set(DOXYGEN_HTML_FOOTER "newfooter.html")
set(DOXYGEN_HTML_EXTRA_STYLESHEET "extrastylesheet.css")
set(DOXYGEN_DISABLE_INDEX "YES")
set(DOXYGEN_GENERATE_TREEVIEW "YES")
set(DOXYGEN_ENUM_VALUES_PER_LINE "0")
set(DOXYGEN_MACRO_EXPANSION "YES")
set(DOXYGEN_PREDEFINED "__declspec(x)=")
set(DOXYGEN_CLASS_DIAGRAMS "NO")


doxygen_add_docs(
    doxygen
    ${DOXY_SOURCES}
    )


install(
    DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}/html
    DESTINATION
        "./doc"
    )
