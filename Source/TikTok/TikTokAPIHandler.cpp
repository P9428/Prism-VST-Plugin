#include "TikTokAPIHandler.h"

TikTokAPIHandler::TikTokAPIHandler() : juce::Thread("TikTokAPI") {}
TikTokAPIHandler::~TikTokAPIHandler() { stopThread(1000); }

void TikTokAPIHandler::authenticateAsync(std::function<void(bool)> cb) {
    callback = cb;
    state = Authorizing;
    startThread();
}

void TikTokAPIHandler::uploadAsync(const juce::File& /*file*/, std::function<void(bool)> cb) {
    callback = cb;
    state = Uploading;
    startThread();
}

void TikTokAPIHandler::run() {
    // Placeholder network operation
    juce::Thread::sleep(500);
    state = Complete;
    if (callback) callback(true);
}
