#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class PrismAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                   private juce::Timer {
public:
    explicit PrismAudioProcessorEditor(PrismAudioProcessor&);
    ~PrismAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;

    PrismAudioProcessor& processor;
    juce::TextButton shareButton { "Share" };
    juce::Label statusLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PrismAudioProcessorEditor)
};
