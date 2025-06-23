#pragma once
#include <JuceHeader.h>
#include "Audio/AudioProcessorChain.h"
#include "TikTok/TikTokAPIHandler.h"
#include "RightsChecker.h"

class PrismAudioProcessor  : public juce::AudioProcessor {
public:
    PrismAudioProcessor();
    ~PrismAudioProcessor() override;

    TikTokAPIHandler& getAPIHandler() { return apiHandler; }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int index) override {}
    const juce::String getProgramName(int index) override { return {}; }
    void changeProgramName(int index, const juce::String& newName) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:
    AudioProcessorChain audioChain;
    TikTokAPIHandler apiHandler;
    RightsChecker rightsChecker;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PrismAudioProcessor)
};
