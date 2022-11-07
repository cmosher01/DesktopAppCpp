set(sources
Foobar.cpp
FoobarApp.cpp
FoobarFrame.cpp
)
add_executable(foobar ${sources})

target_compile_features(foobar PRIVATE cxx_std_17)

find_package(Boost REQUIRED COMPONENTS headers log)
target_compile_definitions(foobar PRIVATE $<TARGET_PROPERTY:Boost::disable_autolinking, INTERFACE_COMPILE_DEFINITIONS>)
target_compile_definitions(foobar PRIVATE $<TARGET_PROPERTY:Boost::dynamic_linking, INTERFACE_COMPILE_DEFINITIONS>)
target_link_libraries(foobar PRIVATE ${Boost_LIBRARIES})

find_package(wxWidgets REQUIRED COMPONENTS base core)
include(${wxWidgets_USE_FILE})
target_link_libraries(foobar PRIVATE ${wxWidgets_LIBRARIES})

install(TARGETS foobar RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
