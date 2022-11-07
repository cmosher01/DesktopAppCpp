set(sources
Foobar.cpp
FoobarApp.cpp
FoobarFrame.cpp
)
add_executable(foobar ${sources})

target_compile_features(foobar PRIVATE cxx_std_17)

set(Boost_USE_STATIC_LIBS FALSE)
set(Boost_USE_MULTITHREADED TRUE)
set(CMAKE_FIND_DEBUG_MODE TRUE) # TODO
find_package(Boost REQUIRED COMPONENTS headers log PATH ${CMAKE_SOURCE_DIR}/lib/boost/stage/x64/Debug/lib/cmake/boost)
set(CMAKE_FIND_DEBUG_MODE FALSE) # TODO
message(STATUS "Boost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS}")
target_include_directories(foobar PRIVATE ${Boost_INCLUDE_DIRS})
message(STATUS "Boost_LIBRARIES=${Boost_LIBRARIES}")
target_link_libraries(foobar ${Boost_LIBRARIES})

find_package(wxWidgets REQUIRED COMPONENTS base core)
include(${wxWidgets_USE_FILE})
target_link_libraries(foobar ${wxWidgets_LIBRARIES})

install(TARGETS foobar RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
