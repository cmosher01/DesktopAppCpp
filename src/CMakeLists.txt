include_directories(../include)

set(sources
FoobarApp.cpp
FoobarFrame.cpp
)
add_executable(foobar ${sources})

target_compile_features(foobar PRIVATE cxx_std_17)
target_link_libraries(foobar wx::core wx::base)

install(TARGETS foobar RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
