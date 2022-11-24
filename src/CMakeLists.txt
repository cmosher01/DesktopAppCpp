set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_NAME foobar)
set(sources
Foobar.cpp
FoobarApp.cpp
FoobarFrame.cpp
PreferencesDialog.cpp
)
set(resources
../share/Resources/Foobar.xrc
)
set(icon_file ${CMAKE_SOURCE_DIR}/${APP_NAME}.png)



add_executable(${APP_NAME} MACOSX_BUNDLE ${sources} ${icon_file} ${resources})



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



set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE TRUE RESOURCE ${resources})
set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_BINARY_DIR}/Info.plist)
set_source_files_properties(${icon_file} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)




include(InstallRequiredSystemLibraries)

if(APPLE)
    install(TARGETS ${APP_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        BUNDLE DESTINATION .)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/FixBundle.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/FixBundle.cmake @ONLY)
    install(SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/FixBundle.cmake)
elseif(WIN32)
    install(TARGETS ${APP_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        BUNDLE DESTINATION .
        RESOURCE DESTINATION .)
    install(TARGETS ${APP_NAME} RUNTIME_DEPENDENCIES
        DIRECTORIES ${CMAKE_SYSTEM_LIBRARY_PATH}
        PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
        POST_EXCLUDE_REGEXES ".*system32/.*\\.dll")
else()
    install(TARGETS ${APP_NAME} RUNTIME_DEPENDENCIES
        DIRECTORIES ${CMAKE_SYSTEM_LIBRARY_PATH}
        RESOURCE DESTINATION share/Resources)
endif()
