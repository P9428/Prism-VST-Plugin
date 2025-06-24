#pragma once
#include <JuceHeader.h>

class LoudnessProcessor {
public:
    void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer);

private:
    double sampleRate = 44100.0;
};
