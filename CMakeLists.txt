cmake_minimum_required(VERSION 3.5)
project(PrismVSTPlugin)

add_library(PrismVSTPlugin SHARED src/PrismPlugin.cpp)

target_include_directories(PrismVSTPlugin PUBLIC include)

if(WIN32)
    set(PLUGIN_SUFFIX ".dll")
    set(PLUGIN_INSTALL_DIR "C:/Program Files/Common Files/VST3")
elseif(APPLE)
    set(PLUGIN_SUFFIX ".dylib")
    set(PLUGIN_INSTALL_DIR "/Library/Audio/Plug-Ins/VST3")
else()
    set(PLUGIN_SUFFIX ".so")
    set(PLUGIN_INSTALL_DIR "$ENV{HOME}/.vst3")
endif()

set_target_properties(PrismVSTPlugin PROPERTIES
    OUTPUT_NAME "PrismVSTPlugin"
    PREFIX ""
    SUFFIX ${PLUGIN_SUFFIX}
)

install(TARGETS PrismVSTPlugin
    RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR}
    LIBRARY DESTINATION ${PLUGIN_INSTALL_DIR}
    ARCHIVE DESTINATION ${PLUGIN_INSTALL_DIR})

add_executable(PluginHost tests/PluginHost.cpp)
target_link_libraries(PluginHost PRIVATE PrismVSTPlugin dl)
add_dependencies(PluginHost PrismVSTPlugin)

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "PrismVSTPlugin")
set(CPACK_PACKAGE_VERSION "0.1.0")
set(CPACK_GENERATOR "ZIP")
include(CPack)
