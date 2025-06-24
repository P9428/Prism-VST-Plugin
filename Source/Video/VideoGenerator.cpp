#include "VideoGenerator.h"

bool VideoGenerator::generateVideo(const juce::File& audioFile, const juce::File& outFile) {
    juce::StringArray args { "ffmpeg", "-y", "-loop", "1", "-i", "background.png",
                             "-i", audioFile.getFullPathName(),
                             "-c:v", "libx264", "-preset", "veryfast",
                             "-shortest", "-pix_fmt", "yuv420p",
                             outFile.getFullPathName() };
    juce::ChildProcess proc;
    return proc.start(args) && proc.waitForProcessToFinish(60000) == 0;
}
