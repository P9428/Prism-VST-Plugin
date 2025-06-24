#include "TikTokAPIHandler.h"
#include "../Video/VideoGenerator.h"
#include "../Audio/AudioProcessorChain.h"

TikTokAPIHandler::TikTokAPIHandler(AudioProcessorChain& chain, RightsChecker& checker)
    : juce::Thread("TikTokAPI"), audioChain(chain), rightsChecker(checker) {}
TikTokAPIHandler::~TikTokAPIHandler() { stopThread(2000); }

void TikTokAPIHandler::authenticateAsync(std::function<void(bool)> cb) {
    callback = cb;
    state = Authorizing;
    startThread();
}

void TikTokAPIHandler::uploadAsync(const juce::File& file, std::function<void(bool)> cb) {
    callback = cb;
    tempAudioFile = file;
    state = Uploading;
    startThread();
}

void TikTokAPIHandler::run() {
    if (state == Authorizing) {
        juce::URL url("https://open.tiktokapis.com/v2/oauth/token/");
        juce::String body = "client_id=" + juce::String(std::getenv("TIKTOK_CLIENT_ID")) +
                            "&client_secret=" + juce::String(std::getenv("TIKTOK_CLIENT_SECRET")) +
                            "&grant_type=client_credentials";
        std::unique_ptr<juce::InputStream> stream(url.withPOSTData(body).createInputStream(false));
        bool ok = stream != nullptr;
        state = ok ? Ready : Failed;
        if (callback) juce::MessageManager::callAsync([this, ok]{ callback(ok); });
        return;
    }

    if (state == Uploading) {
        // Wait for buffered audio and write to temp file
        juce::AudioBuffer<float> buf(2, 512);
        juce::WavAudioFormat fmt;
        std::unique_ptr<juce::FileOutputStream> out(tempAudioFile.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(fmt.createWriterFor(out.get(), 44100.0, 2, 16, {}, 0));
        if (!writer) {
            state = Failed;
            if (callback) juce::MessageManager::callAsync([this]{ callback(false); });
            return;
        }
        while (audioChain.popProcessedAudio(buf)) {
            writer->writeFromAudioSampleBuffer(buf, 0, buf.getNumSamples());
            if (threadShouldExit()) break;
        }
        out.release();

        // Rights check
        juce::MemoryBlock audioData;
        bool rightsOk = tempAudioFile.loadFileAsData(audioData);
        if (rightsOk) {
            juce::URL url("https://identify-eu-west-1.acrcloud.com/v1/identify");
            juce::String token = juce::String(std::getenv("ACRCLOUD_TOKEN"));
            juce::StringPairArray headers;
            headers.set("Authorization", "Bearer " + token);
            headers.set("Content-Type", "application/octet-stream");
            std::unique_ptr<juce::InputStream> s(url.createInputStream(false, nullptr, nullptr, headers, (int)audioData.getSize(), audioData.getData()));
            rightsOk = s != nullptr;
        }
        if (!rightsOk) {
            state = Failed;
            if (callback) juce::MessageManager::callAsync([this]{ callback(false); });
            return;
        }

        VideoGenerator video;
        juce::File videoFile = tempAudioFile.getSiblingFile("tiktok.mp4");
        bool videoOk = video.generateVideo(tempAudioFile, videoFile);

        if (!videoOk) {
            state = Failed;
            if (callback) juce::MessageManager::callAsync([this]{ callback(false); });
            return;
        }

        // Placeholder upload request
        juce::URL uploadUrl("https://open.tiktokapis.com/v2/post/content/");
        uploadUrl = uploadUrl.withFileToUpload("video", videoFile, "video/mp4");
        std::unique_ptr<juce::InputStream> stream(uploadUrl.createInputStream(false));
        bool ok = stream != nullptr;
        state = ok ? Complete : Failed;
        if (callback) juce::MessageManager::callAsync([this, ok]{ callback(ok); });
    }
}
