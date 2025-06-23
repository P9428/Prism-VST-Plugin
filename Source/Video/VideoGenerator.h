#pragma once
#include <JuceHeader.h>

class VideoGenerator {
public:
    bool generateVideo(const juce::File& audioFile, const juce::File& outFile);
};
