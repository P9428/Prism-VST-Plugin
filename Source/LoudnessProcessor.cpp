#include "LoudnessProcessor.h"

void LoudnessProcessor::prepare(double sr, int /*samplesPerBlock*/) {
    sampleRate = sr;

    auto preCoeffs = juce::dsp::IIR::Coefficients<float>::makeHighPass(sr, 40.0);
    auto weightCoeffs = juce::dsp::IIR::Coefficients<float>::makeHighShelf(sr, 1500.0, 0.5f, juce::Decibels::decibelsToGain(4.0f));
    preFilterL.state = preCoeffs;
    preFilterR.state = preCoeffs;
    weightingFilterL.state = weightCoeffs;
    weightingFilterR.state = weightCoeffs;
}

void LoudnessProcessor::process(juce::AudioBuffer<float>& buffer) {
    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();

    float sumSquares = 0.0f;
    for (int ch = 0; ch < numChannels; ++ch) {
        auto* data = buffer.getWritePointer(ch);
        juce::dsp::AudioBlock<float> block(data, 1, (size_t)numSamples);
        if (ch == 0) {
            preFilterL.process(juce::dsp::ProcessContextReplacing<float>(block));
            weightingFilterL.process(juce::dsp::ProcessContextReplacing<float>(block));
        } else {
            preFilterR.process(juce::dsp::ProcessContextReplacing<float>(block));
            weightingFilterR.process(juce::dsp::ProcessContextReplacing<float>(block));
        }
        for (int i = 0; i < numSamples; ++i) {
            data[i] = juce::jlimit(-0.891f, 0.891f, data[i]);
            sumSquares += data[i] * data[i];
        }
    }

    float rms = std::sqrt(sumSquares / (numSamples * numChannels));
    float currentDb = juce::Decibels::gainToDecibels(rms, -100.0f);
    const float targetDb = -14.0f;
    float gain = juce::Decibels::decibelsToGain(targetDb - currentDb);

    buffer.applyGain(gain);

    accumulatedEnergy += sumSquares;
    processedSamples += (uint64_t)numSamples * (uint64_t)numChannels;
    if (processedSamples > 0) {
        integratedLufs = -0.691f + 10.0f * std::log10(accumulatedEnergy / processedSamples + 1e-12f);
    }
}
