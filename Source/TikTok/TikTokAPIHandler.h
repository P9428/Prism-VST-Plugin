#pragma once
#include <JuceHeader.h>
#include "../RightsChecker.h"

class TikTokAPIHandler : public juce::Thread {
public:
    TikTokAPIHandler(AudioProcessorChain& chain, RightsChecker& checker);
    ~TikTokAPIHandler() override;

    void authenticateAsync(std::function<void(bool)> cb);
    void uploadAsync(const juce::File& file, std::function<void(bool)> cb);
    enum State { Ready, Authorizing, GeneratingVideo, Uploading, Processing, Complete, Failed };
    State getState() const { return state; }

    void run() override;

private:
    std::function<void(bool)> callback;
    State state = Ready;
    juce::URL authUrl;
    AudioProcessorChain& audioChain;
    RightsChecker& rightsChecker;
    juce::File tempAudioFile;
};
