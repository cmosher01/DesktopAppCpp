set(sources
Foobar.cpp
FoobarApp.cpp
FoobarFrame.cpp
)
add_executable(foobar ${sources})

target_compile_features(foobar PRIVATE cxx_std_17)

find_package(Boost REQUIRED COMPONENTS headers log)
if(WIN32)
    # TODO: see if anyone ever fixes whatever bug requires us to set these two:
    set_target_properties(foobar PROPERTIES COMPILE_DEFINITIONS BOOST_ALL_DYN_LINK)
    set_target_properties(foobar PROPERTIES COMPILE_DEFINITIONS BOOST_ALL_NO_LIB)
    set_target_properties(foobar PROPERTIES COMPILE_DEFINITIONS BOOST_USE_WINAPI_VERSION=0x0A00)
endif()
message(STATUS "Boost_LIBRARIES=${Boost_LIBRARIES}")
target_link_libraries(foobar PRIVATE ${Boost_LIBRARIES})

find_package(wxWidgets REQUIRED COMPONENTS base core)
include(${wxWidgets_USE_FILE})
target_link_libraries(foobar PRIVATE ${wxWidgets_LIBRARIES})

install(TARGETS foobar RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
