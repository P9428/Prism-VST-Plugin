cmake_minimum_required(VERSION 3.15)
project(PrismVST)

option(JUCE_DIR "Path to the JUCE framework" "${CMAKE_SOURCE_DIR}/../JUCE")

if(NOT EXISTS ${JUCE_DIR})
    message(FATAL_ERROR "JUCE not found at ${JUCE_DIR}. Set JUCE_DIR to your JUCE directory.")
endif()

# TODO: add plugin targets that use JUCE

