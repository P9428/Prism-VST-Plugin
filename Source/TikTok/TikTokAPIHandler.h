#pragma once
#include <JuceHeader.h>

class TikTokAPIHandler : public juce::Thread {
public:
    TikTokAPIHandler();
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
};
