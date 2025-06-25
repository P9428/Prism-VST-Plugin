#pragma once
#include <JuceHeader.h>

class LoudnessProcessor {
public:
    LoudnessProcessor() = default;

    void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer);
    float getIntegratedLufs() const { return integratedLufs; }

private:
    double sampleRate = 44100.0;
    juce::dsp::IIR::Filter<float> preFilterL, preFilterR;
    juce::dsp::IIR::Filter<float> weightingFilterL, weightingFilterR;
    double accumulatedEnergy = 0.0;
    uint64_t processedSamples = 0;
    float integratedLufs = 0.0f;
};
