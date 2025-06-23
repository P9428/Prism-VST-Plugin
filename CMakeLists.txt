cmake_minimum_required(VERSION 3.15)
project(PrismVST VERSION 0.1.0)

set(JUCE_DIR "${CMAKE_SOURCE_DIR}/JUCE")
add_subdirectory(${JUCE_DIR})

juce_add_plugin(PrismVST
    COMPANY_NAME Prism
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Prsm
    PLUGIN_CODE Pmst
    FORMATS VST3 AU
    PRODUCT_NAME "PrismVST")

target_sources(PrismVST PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/LoudnessProcessor.cpp
    Source/LoudnessProcessor.h
    Source/TikTokUploader.cpp
    Source/TikTokUploader.h
    Source/RightsChecker.cpp
    Source/RightsChecker.h
    Source/Audio/AudioProcessorChain.cpp
    Source/Audio/AudioProcessorChain.h
    Source/TikTok/TikTokAPIHandler.cpp
    Source/TikTok/TikTokAPIHandler.h
    Source/Video/VideoGenerator.cpp
    Source/Video/VideoGenerator.h)

target_compile_features(PrismVST PRIVATE cxx_std_17)

target_link_libraries(PrismVST PRIVATE
    juce::juce_audio_utils
    juce::juce_gui_extra)
