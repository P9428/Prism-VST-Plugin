#include "LoudnessProcessor.h"

void LoudnessProcessor::prepare(double sr, int /*samplesPerBlock*/) {
    sampleRate = sr;
}

void LoudnessProcessor::process(juce::AudioBuffer<float>& buffer) {
    // Simple peak limiting and normalization placeholder.
    auto numSamples = buffer.getNumSamples();
    for (int ch = 0; ch < buffer.getNumChannels(); ++ch) {
        auto* data = buffer.getWritePointer(ch);
        for (int i = 0; i < numSamples; ++i) {
            if (data[i] > 1.0f) data[i] = 1.0f;
            if (data[i] < -1.0f) data[i] = -1.0f;
            // TODO: implement LUFS measurement and normalization
        }
    }
}
