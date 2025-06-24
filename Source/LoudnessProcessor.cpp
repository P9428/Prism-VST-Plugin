#include "LoudnessProcessor.h"

void LoudnessProcessor::prepare(double sr, int /*samplesPerBlock*/) {
    sampleRate = sr;
}

void LoudnessProcessor::process(juce::AudioBuffer<float>& buffer) {
    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();

    float sumSquares = 0.0f;
    for (int ch = 0; ch < numChannels; ++ch) {
        auto* data = buffer.getWritePointer(ch);
        for (int i = 0; i < numSamples; ++i) {
            // Peak limiting at -1 dBTP
            data[i] = juce::jlimit(-0.891f, 0.891f, data[i]);
            sumSquares += data[i] * data[i];
        }
    }

    // Calculate RMS level for normalization
    float rms = std::sqrt(sumSquares / (numSamples * numChannels));
    float currentDb = juce::Decibels::gainToDecibels(rms, -100.0f);
    const float targetDb = -14.0f; // approximate LUFS target
    float gain = juce::Decibels::decibelsToGain(targetDb - currentDb);

    buffer.applyGain(gain);
}
