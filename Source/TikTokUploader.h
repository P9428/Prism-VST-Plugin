#pragma once
#include <JuceHeader.h>

class TikTokUploader {
public:
    TikTokUploader();
    ~TikTokUploader();

    void authenticateAsync(std::function<void(bool)> callback);
    void uploadAsync(const juce::File& file, std::function<void(bool)> callback);

private:
    juce::String accessToken;
};
