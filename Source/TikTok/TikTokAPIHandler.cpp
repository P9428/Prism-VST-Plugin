#include "TikTokAPIHandler.h"
#include "../Video/VideoGenerator.h"

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

void TikTokAPIHandler::finish(bool success) {
    State finalState = success ? Ready : Failed;
    state = finalState;
    if (callback)
        juce::MessageManager::callAsync([this, success] { callback(success); });
}

void TikTokAPIHandler::run() {
    if (state == Authorizing) {
        juce::String clientId = juce::String(std::getenv("TIKTOK_CLIENT_ID"));
        juce::String clientSecret = juce::String(std::getenv("TIKTOK_CLIENT_SECRET"));
        if (clientId.isEmpty() || clientSecret.isEmpty()) { finish(false); return; }

        codeVerifier = juce::Uuid().toString();
        juce::String redirectUri = "http://127.0.0.1:53682/callback";
        juce::URL auth("https://www.tiktok.com/auth/authorize/");
        auth = auth.withParameter("client_key", clientId)
                   .withParameter("scope", "video.upload,user.info.basic")
                   .withParameter("response_type", "code")
                   .withParameter("redirect_uri", redirectUri)
                   .withParameter("code_challenge", codeVerifier)
                   .withParameter("code_challenge_method", "plain");
        auth.launchInDefaultBrowser();

        juce::StreamingSocket server;
        if (!server.createListener(53682, "127.0.0.1")) { finish(false); return; }
        std::unique_ptr<juce::StreamingSocket> incoming(server.waitForNextConnection());
        if (!incoming) { finish(false); return; }
        char buffer[1024] = {0};
        int bytes = incoming->read(buffer, sizeof(buffer), true);
        juce::String request(juce::String::fromUTF8(buffer, bytes));
        int index = request.indexOf("/callback?code=");
        if (index < 0) { finish(false); return; }
        juce::String code = request.fromFirstOccurrenceOf("/callback?code=", false, false)
                                 .upToFirstOccurrenceOf(" ", false, false)
                                 .fromFirstOccurrenceOf("=", false, false);
        juce::String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nLogin complete. You may close this window.";
        incoming->write(response.toRawUTF8(), (int)response.getNumBytesAsUTF8());
        server.close();

        juce::URL tokenUrl("https://open.tiktokapis.com/v2/oauth/token/");
        juce::String body = "client_key=" + clientId + "&client_secret=" + clientSecret +
                            "&code=" + code + "&grant_type=authorization_code" +
                            "&redirect_uri=" + redirectUri + "&code_verifier=" + codeVerifier;
        auto stream = tokenUrl.withPOSTData(body).createInputStream(false);
        if (!stream) { finish(false); return; }
        auto responseStr = stream->readEntireStreamAsString();
        auto json = juce::JSON::parse(responseStr);
        accessToken = json["access_token"].toString();
        refreshToken = json["refresh_token"].toString();
        finish(!accessToken.isEmpty());
        return;
    }

    if (state == Uploading) {
        juce::AudioBuffer<float> buf(2, 512);
        juce::WavAudioFormat fmt;
        std::unique_ptr<juce::FileOutputStream> out(tempAudioFile.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(fmt.createWriterFor(out.get(), 44100.0, 2, 16, {}, 0));
        if (!writer) { finish(false); return; }
        while (audioChain.popProcessedAudio(buf)) {
            writer->writeFromAudioSampleBuffer(buf, 0, buf.getNumSamples());
            if (threadShouldExit()) break;
        }
        out.release();

        std::atomic<bool> rightsOk{false};
        std::atomic<bool> doneFlag{false};
        rightsChecker.checkAudioAsync(tempAudioFile, [&rightsOk,&doneFlag](bool ok){ rightsOk = ok; doneFlag = true; });
        while (!doneFlag && !threadShouldExit()) { juce::Thread::sleep(50); }
        if (!rightsOk) { finish(false); return; }

        VideoGenerator video;
        juce::File videoFile = tempAudioFile.getSiblingFile("tiktok.mp4");
        if (!video.generateVideo(tempAudioFile, videoFile)) { finish(false); return; }

        juce::URL uploadUrl("https://open.tiktokapis.com/v2/post/publish/inbox/video/");
        juce::StringPairArray headers;
        headers.set("Authorization", "Bearer " + accessToken);
        uploadUrl = uploadUrl.withFileToUpload("video_file", videoFile, "video/mp4");
        auto stream = uploadUrl.createInputStream(false, nullptr, nullptr, headers);
        if (!stream) { finish(false); return; }
        auto uploadResponse = stream->readEntireStreamAsString();
        juce::ignoreUnused(uploadResponse);
        finish(true);
    }
}
