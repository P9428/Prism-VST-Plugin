#include "PluginEditor.h"
#include "PluginProcessor.h"

PrismAudioProcessorEditor::PrismAudioProcessorEditor(PrismAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p) {
    addAndMakeVisible(shareButton);
    addAndMakeVisible(statusLabel);
    statusLabel.setJustificationType(juce::Justification::centred);

    shareButton.onClick = [this] {
        statusLabel.setText("Authorizing...", juce::dontSendNotification);
        processor.getAPIHandler().authenticateAsync([this](bool ok) {
            if (!ok) {
                statusLabel.setText("Auth Failed", juce::dontSendNotification);
                return;
            }
            statusLabel.setText("Uploading...", juce::dontSendNotification);
            juce::File temp = juce::File::getSpecialLocation(juce::File::tempDirectory)
                                   .getChildFile("prism_audio.wav");
            processor.getAPIHandler().uploadAsync(temp, [this](bool success) {
                statusLabel.setText(success ? "Complete" : "Failed", juce::dontSendNotification);
            });
        });
    };
    startTimerHz(2);
    setSize(400, 150);
}

PrismAudioProcessorEditor::~PrismAudioProcessorEditor() {}

void PrismAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Prism VST3", getLocalBounds().removeFromTop(30), juce::Justification::centred, 1);
}

void PrismAudioProcessorEditor::resized() {
    auto area = getLocalBounds().reduced(20);
    shareButton.setBounds(area.removeFromTop(30));
    statusLabel.setBounds(area.removeFromTop(20));
}

void PrismAudioProcessorEditor::timerCallback() {
    using State = TikTokAPIHandler::State;
    switch (processor.getAPIHandler().getState()) {
        case State::Authorizing: statusLabel.setText("Authorizing...", juce::dontSendNotification); break;
        case State::Uploading:   statusLabel.setText("Uploading...", juce::dontSendNotification); break;
        case State::Processing:  statusLabel.setText("Processing...", juce::dontSendNotification); break;
        case State::Complete:    statusLabel.setText("Complete", juce::dontSendNotification); break;
        case State::Failed:      statusLabel.setText("Failed", juce::dontSendNotification); break;
        default: break;
    }
}
