cmake_minimum_required(VERSION 3.5)
project(PrismVSTPlugin)

add_library(PrismVSTPlugin SHARED src/PrismPlugin.cpp)

target_include_directories(PrismVSTPlugin PUBLIC include)

set_target_properties(PrismVSTPlugin PROPERTIES
    OUTPUT_NAME "PrismVSTPlugin"
    PREFIX ""
    SUFFIX ".so"
)

add_executable(PluginHost tests/PluginHost.cpp)
target_link_libraries(PluginHost PRIVATE PrismVSTPlugin dl)
add_dependencies(PluginHost PrismVSTPlugin)
