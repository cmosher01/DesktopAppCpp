set(sources
Foobar.cpp
FoobarApp.cpp
FoobarFrame.cpp
)
add_executable(foobar ${sources})

target_compile_features(foobar PRIVATE cxx_std_17)

set(Boost_DEBUG TRUE) # TODO
find_package(Boost REQUIRED COMPONENTS log)
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
    BOOST_LIB_DIAGNOSTIC)
message(STATUS "Boost_LIBRARIES=${Boost_LIBRARIES}")
target_link_libraries(foobar PRIVATE ${Boost_LIBRARIES})

find_package(wxWidgets REQUIRED COMPONENTS base core)
include(${wxWidgets_USE_FILE})
target_link_libraries(foobar PRIVATE ${wxWidgets_LIBRARIES})

install(TARGETS foobar RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})



# set(CMAKE_FIND_DEBUG_MODE TRUE) # TODO
# set(CMAKE_FIND_DEBUG_MODE FALSE) # TODO

