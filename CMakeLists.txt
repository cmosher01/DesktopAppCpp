cmake_minimum_required(VERSION 3.22.1)
cmake_policy(SET CMP0048 NEW)



macro(pv v)
    message(STATUS "${v}=${${v}}")
endmacro()





project(foobar
VERSION 0.0.1
DESCRIPTION "A desktop application example"
HOMEPAGE_URL https://github.com/cmosher01/DesktopAppCpp
LANGUAGES CXX
)





pv(PROJECT_SOURCE_DIR)
pv(PROJECT_BINARY_DIR)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory; make a build subdirectory.")
endif()



set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)

include(GNUInstallDirs)

set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}")
include_directories(BEFORE "${CMAKE_SOURCE_DIR}/include")



pv(CMAKE_SYSTEM)
pv(CMAKE_SYSTEM_NAME)

pv(CPACK_PACKAGING_INSTALL_PREFIX)
pv(CMAKE_INSTALL_PREFIX)

pv(CMAKE_INSTALL_BINDIR)
pv(CMAKE_INSTALL_FULL_BINDIR)
pv(CMAKE_INSTALL_LIBDIR)
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




set(CPACK_PACKAGE_VENDOR "mosher.mine.nu")
set(CPACK_PACKAGE_CONTACT "cmosher01@gmail.com")

set(CPACK_GENERATOR ZIP TGZ 7Z)
if(WIN32)
    set(CPACK_GENERATOR ${CPACK_GENERATOR} NSIS)
elseif(APPLE)
    set(CPACK_GENERATOR ${CPACK_GENERATOR} DragNDrop)
else()
    set(CPACK_GENERATOR ${CPACK_GENERATOR} DEB)
endif()

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-dev, libwxgtk3.0-gtk3-0v5")

include(CPack)
