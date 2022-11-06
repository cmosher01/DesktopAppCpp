set(sources
Foobar.cpp
FoobarApp.cpp
FoobarFrame.cpp
)
add_executable(foobar ${sources})

target_compile_features(foobar PRIVATE cxx_std_17)

#find_package(Boost REQUIRED COMPONENTS log PATHS "${CMAKE_SOURCE_DIR}/lib/boost/stage/x64/Release/lib/cmake/Boost-1.80.0")
#message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
#target_include_directories(foobar PRIVATE ${Boost_INCLUDE_DIRS})
#message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
#target_link_libraries(foobar ${Boost_LIBRARIES})

# target_link_libraries(foobar wx::base)
# wx::core

# install(TARGETS foobar RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
