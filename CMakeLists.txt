cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_VERBOSE_MAKEFILE TRUE CACHE BOOL "Echo make commands.")
set(PACKAGE_SUITE TRUE CACHE BOOL "Build entire suite of packages; otherwise just ZIP file.")

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)





set(APP_NAME foobar)

project(${APP_NAME}
    VERSION 0.0.2
    DESCRIPTION "A desktop application example"
    HOMEPAGE_URL https://github.com/cmosher01/DesktopAppCpp
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_FOURCC epl2)
set(PROJECT_VENDOR "nu.mine.mosher")
set(CPACK_PACKAGE_VENDOR "${PROJECT_VENDOR}")
set(CPACK_PACKAGE_CONTACT "cmosher01@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION "${PROJECT_DESCRIPTION}")

set(sources
Foobar.cpp
FoobarApp.cpp
FoobarFrame.cpp
PreferencesDialog.cpp
)
list(TRANSFORM sources PREPEND "src/")

set(resources
Foobar.xrc
foobar.png
config/.template.conf
)
list(TRANSFORM resources PREPEND "share/Resources/")





file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory; make a build subdirectory.")
endif()



if(WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/Program Files/${PROJECT_NAME}")
    unset(CPACK_PACKAGING_INSTALL_PREFIX)
elseif(APPLE)
    unset(CMAKE_INSTALL_PREFIX)
    unset(CPACK_PACKAGING_INSTALL_PREFIX)
else()
    set(CMAKE_INSTALL_PREFIX "/opt/${CPACK_PACKAGE_VENDOR}/${PROJECT_NAME}")
    set(CPACK_PACKAGING_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
endif()

include(GNUInstallDirs)

include_directories(BEFORE "include")





add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE ${sources} ${resources})



find_package(Boost REQUIRED COMPONENTS log filesystem)
# These settings must match those of the installed boost libraries.
# Use objdump to check the "namespace", such as "v2_mt_nt6"
# https://www.boost.org/doc/libs/master/libs/log/doc/html/log/rationale/namespace_mangling.html
target_compile_definitions(${APP_NAME} PRIVATE
    BOOST_ALL_DYN_LINK
    BOOST_ATOMIC_DYN_LINK
    BOOST_CHRONO_DYN_LINK
    BOOST_FILESYSTEM_DYN_LINK
    BOOST_LIB_DIAGNOSTIC
    BOOST_LOG_DYN_LINK
    BOOST_REGEX_DYN_LINK
    BOOST_THREAD_DYN_LINK
    BOOST_ALL_NO_LIB
    BOOST_LIB_DIAGNOSTIC
    BOOST_USE_WINAPI_VERSION=0x0600)
target_link_libraries(${APP_NAME} PRIVATE ${Boost_LIBRARIES})

find_package(wxWidgets REQUIRED COMPONENTS base core xrc)
include(${wxWidgets_USE_FILE})
target_link_libraries(${APP_NAME} PRIVATE ${wxWidgets_LIBRARIES})



configure_file(include/config.h.in config.h)
include_directories(${PROJECT_BINARY_DIR})



set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${resources}")





include(InstallRequiredSystemLibraries)

if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST ${PROJECT_BINARY_DIR}/Info.plist)
    install(TARGETS ${APP_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        BUNDLE DESTINATION .)
    configure_file(share/FixBundle.cmake.in ${PROJECT_BINARY_DIR}/FixBundle.cmake @ONLY)
    install(SCRIPT ${PROJECT_BINARY_DIR}/FixBundle.cmake)
elseif(WIN32)
    install(TARGETS ${APP_NAME}
        RUNTIME_DEPENDENCIES
            DIRECTORIES ${CMAKE_SYSTEM_LIBRARY_PATH}
            PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
            POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
        BUNDLE DESTINATION .
        RESOURCE DESTINATION share/Resources)
else()
    install(TARGETS ${APP_NAME}
        RUNTIME_DEPENDENCIES
            DIRECTORIES ${CMAKE_SYSTEM_LIBRARY_PATH}
        RESOURCE DESTINATION share/Resources)
endif()





set(CPACK_GENERATOR ZIP)

if(PACKAGE_SUITE)
    set(CPACK_GENERATOR ${CPACK_GENERATOR} TGZ 7Z)
    if(APPLE)
        set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-macOS")
        configure_file(share/Info.plist.in ${PROJECT_BINARY_DIR}/Info.plist)
        set(CPACK_GENERATOR ${CPACK_GENERATOR} DragNDrop)
    elseif(WIN32)
        set(CPACK_GENERATOR ${CPACK_GENERATOR} NSIS)
    else()
        set(CPACK_GENERATOR ${CPACK_GENERATOR} DEB)
    endif()
endif()

include(CPack)
