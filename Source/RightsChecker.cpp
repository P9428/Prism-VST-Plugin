#include "RightsChecker.h"

RightsChecker::RightsChecker() {}
RightsChecker::~RightsChecker() {}

void RightsChecker::checkAudioAsync(const juce::File& file, std::function<void(bool)> callback) {
    // TODO: integrate with a fingerprinting service
    juce::Thread::launch([callback] { callback(true); });
}
