set(sources
Foobar.cpp
FoobarApp.cpp
FoobarFrame.cpp
)
add_executable(foobar ${sources})

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS log log_setup)
# These settings must match those of the installed boost libraries.
# Use objdump to check the "namespace", such as "v2_mt_nt6"
# https://www.boost.org/doc/libs/master/libs/log/doc/html/log/rationale/namespace_mangling.html
target_compile_definitions(foobar PRIVATE
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
target_link_libraries(foobar PRIVATE ${Boost_LIBRARIES})

find_package(wxWidgets REQUIRED COMPONENTS base core)
include(${wxWidgets_USE_FILE})
target_link_libraries(foobar PRIVATE ${wxWidgets_LIBRARIES})

install(TARGETS foobar RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS foobar RUNTIME_DEPENDENCIES)
