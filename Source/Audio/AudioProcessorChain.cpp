#include "AudioProcessorChain.h"

void AudioProcessorChain::prepare(double sr, int /*blockSize*/) {
    sampleRate = sr;
}

void AudioProcessorChain::pushAudio(const juce::AudioBuffer<float>& buffer) {
    const int numSamples = buffer.getNumSamples();
    int start1, size1, start2, size2;
    fifo.prepareToWrite(numSamples, start1, size1, start2, size2);
    if (size1 > 0) {
        for (int ch=0; ch<buffer.getNumChannels(); ++ch)
            ringBuffer.copyFrom(ch, start1, buffer, ch, 0, size1);
    }
    if (size2 > 0) {
        for (int ch=0; ch<buffer.getNumChannels(); ++ch)
            ringBuffer.copyFrom(ch, start2, buffer, ch, size1, size2);
    }
    fifo.finishedWrite(size1 + size2);
}

bool AudioProcessorChain::popProcessedAudio(juce::AudioBuffer<float>& dest) {
    const int numSamples = dest.getNumSamples();
    int start1, size1, start2, size2;
    fifo.prepareToRead(numSamples, start1, size1, start2, size2);
    if (size1 + size2 < numSamples) {
        fifo.finishedRead(size1 + size2);
        return false;
    }
    if (size1 > 0) {
        for (int ch=0; ch<dest.getNumChannels(); ++ch)
            dest.copyFrom(ch, 0, ringBuffer, ch, start1, size1);
    }
    if (size2 > 0) {
        for (int ch=0; ch<dest.getNumChannels(); ++ch)
            dest.copyFrom(ch, size1, ringBuffer, ch, start2, size2);
    }
    fifo.finishedRead(size1 + size2);
    // TODO: apply loudness normalization and encoding
    return true;
}
