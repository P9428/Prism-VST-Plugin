#include "PluginProcessor.h"
#include "PluginEditor.h"

PrismAudioProcessor::PrismAudioProcessor() {}
PrismAudioProcessor::~PrismAudioProcessor() {}

const juce::String PrismAudioProcessor::getName() const { return JucePlugin_Name; }

bool PrismAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void PrismAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    audioChain.prepare(sampleRate, samplesPerBlock);
}

void PrismAudioProcessor::releaseResources() {}

void PrismAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    juce::ScopedNoDenormals noDenormals;
    audioChain.pushAudio(buffer);
}

juce::AudioProcessorEditor* PrismAudioProcessor::createEditor() { return new PrismAudioProcessorEditor(*this); }
bool PrismAudioProcessor::hasEditor() const { return true; }

void PrismAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {}
void PrismAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {}
