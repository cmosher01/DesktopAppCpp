set(sources
Foobar.cpp
FoobarApp.cpp
FoobarFrame.cpp
)
add_executable(foobar ${sources})

target_compile_features(foobar PRIVATE cxx_std_17)

find_package(Boost REQUIRED COMPONENTS log)
# TODO: try to have cmake set these compiler defs automatically (broken on MSYS builds?):
target_compile_definitions(foobar PRIVATE BOOST_ALL_DYN_LINK BOOST_ALL_NO_LIB BOOST_LIB_DIAGNOSTIC)
message(STATUS "Boost_LIBRARIES=${Boost_LIBRARIES}")
target_link_libraries(foobar PRIVATE ${Boost_LIBRARIES})

find_package(wxWidgets REQUIRED COMPONENTS base core)
include(${wxWidgets_USE_FILE})
target_link_libraries(foobar PRIVATE ${wxWidgets_LIBRARIES})

install(TARGETS foobar RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})



# set(CMAKE_FIND_DEBUG_MODE TRUE) # TODO
# set(CMAKE_FIND_DEBUG_MODE FALSE) # TODO
