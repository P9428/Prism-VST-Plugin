#include "PluginEditor.h"
#include "PluginProcessor.h"

PrismAudioProcessorEditor::PrismAudioProcessorEditor(PrismAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p) {
    setSize(400, 300);
}

PrismAudioProcessorEditor::~PrismAudioProcessorEditor() {}

void PrismAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Prism VST3", getLocalBounds(), juce::Justification::centred, 1);
}

void PrismAudioProcessorEditor::resized() {}
