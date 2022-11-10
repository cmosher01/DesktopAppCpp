set(APP_NAME foobar)
set(sources
Foobar.cpp
FoobarApp.cpp
FoobarFrame.cpp
)
add_executable(${APP_NAME} ${sources})

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS log log_setup)
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

find_package(wxWidgets REQUIRED COMPONENTS base core)
include(${wxWidgets_USE_FILE})
target_link_libraries(${APP_NAME} PRIVATE ${wxWidgets_LIBRARIES})

install(TARGETS ${APP_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
if (NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    install(TARGETS ${APP_NAME} RUNTIME_DEPENDENCIES
        DIRECTORIES "C:\\msys64\\mingw64\\bin"
        PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
        POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
        FRAMEWORK DESTINATION "${APP_NAME}.app/Contents/Frameworks"
    )
endif()
