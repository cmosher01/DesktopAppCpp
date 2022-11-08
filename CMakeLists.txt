cmake_minimum_required(VERSION 3.22.1)

macro(pv v)
    message(STATUS "${v}=${${v}}")
endmacro()





project(foobar)





pv(PROJECT_SOURCE_DIR)
pv(PROJECT_BINARY_DIR)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory; make a build subdirectory.")
endif()



set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)

set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}")
include_directories(BEFORE "${CMAKE_SOURCE_DIR}/include")

include(GNUInstallDirs)





pv(CPACK_PACKAGING_INSTALL_PREFIX)
pv(CMAKE_INSTALL_PREFIX)

pv(CMAKE_INSTALL_BINDIR)
pv(CMAKE_INSTALL_FULL_BINDIR)
pv(CMAKE_INSTALL_SYSCONFDIR)
pv(CMAKE_INSTALL_FULL_SYSCONFDIR)

pv(CMAKE_SYSTEM_PREFIX_PATH)
pv(CMAKE_SYSTEM_PROGRAM_PATH)
pv(CMAKE_SYSTEM_LIBRARY_PATH)
pv(CMAKE_SYSTEM_INCLUDE_PATH)

pv(CMAKE_PREFIX_PATH)
pv(CMAKE_PROGRAM_PATH)
pv(CMAKE_LIBRARY_PATH)
pv(CMAKE_INCLUDE_PATH)





add_subdirectory(src)

include(CPack)
