#pragma once
#include <JuceHeader.h>

class AudioProcessorChain {
public:
    void prepare(double sampleRate, int samplesPerBlock);
    void pushAudio(const juce::AudioBuffer<float>& buffer);
    bool popProcessedAudio(juce::AudioBuffer<float>& dest);

private:
    juce::AbstractFifo fifo { 16384 };
    juce::AudioBuffer<float> ringBuffer {2, 16384};
    double sampleRate = 44100.0;
};
