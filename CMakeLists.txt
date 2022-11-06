cmake_minimum_required(VERSION 3.22.1)

project(foobar)

message(VERBOSE "PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}")
message(VERBOSE "PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory; make a build subdirectory.")
endif()

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)

message(VERBOSE "CPACK_PACKAGING_INSTALL_PREFIX=${CPACK_PACKAGING_INSTALL_PREFIX}")
message(VERBOSE "CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")

include(GNUInstallDirs)
message(VERBOSE "CMAKE_INSTALL_BINDIR=${CMAKE_INSTALL_BINDIR}")
message(VERBOSE "CMAKE_INSTALL_FULL_BINDIR=${CMAKE_INSTALL_FULL_BINDIR}")
message(VERBOSE "CMAKE_INSTALL_SYSCONFDIR=${CMAKE_INSTALL_SYSCONFDIR}")
message(VERBOSE "CMAKE_INSTALL_FULL_SYSCONFDIR=${CMAKE_INSTALL_FULL_SYSCONFDIR}")

# set(CMAKE_FIND_DEBUG_MODE TRUE)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib/cmake")
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}")
include_directories(include)

set(CPM_URL "https://github.com/TheLartians/CPM.cmake/releases/latest/download/CPM.cmake")
file(DOWNLOAD "${CPM_URL}" "${CMAKE_SOURCE_DIR}/lib/cmake/CPM.cmake")
include(CPM)

# add_subdirectory(lib)
add_subdirectory(src)

include(CPack)
