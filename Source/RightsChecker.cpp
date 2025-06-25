#include "RightsChecker.h"

RightsChecker::RightsChecker() {}
RightsChecker::~RightsChecker() {}

void RightsChecker::checkAudioAsync(const juce::File& file, std::function<void(bool)> callback) {
    juce::Thread::launch([file, callback] {
        juce::MemoryBlock audioData;
        if (!file.loadFileAsData(audioData)) {
            juce::MessageManager::callAsync([callback]{ callback(false); });
            return;
        }

        juce::URL url("https://identify-eu-west-1.acrcloud.com/v1/identify");
        juce::String token = juce::String(std::getenv("ACRCLOUD_TOKEN"));
        juce::StringPairArray headers;
        headers.set("Authorization", "Bearer " + token);
        headers.set("Content-Type", "application/octet-stream");
        std::unique_ptr<juce::InputStream> stream(url.createInputStream(false, nullptr, nullptr, headers, (int)audioData.getSize(), audioData.getData()));
        bool ok = stream != nullptr;
        juce::MessageManager::callAsync([callback, ok]{ callback(ok); });
    });
}
