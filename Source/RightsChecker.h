#pragma once
#include <JuceHeader.h>

class RightsChecker {
public:
    RightsChecker();
    ~RightsChecker();

    void checkAudioAsync(const juce::File& file, std::function<void(bool)> callback);
};
