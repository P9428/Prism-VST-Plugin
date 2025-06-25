#include "VideoGenerator.h"

bool VideoGenerator::generateVideo(const juce::File& audioFile, const juce::File& outFile) {
    juce::StringArray args{
        "ffmpeg", "-y",
        "-loop", "1", "-i", "background.png",
        "-i", audioFile.getFullPathName(),
        "-c:v", "libx264", "-tune", "stillimage", "-pix_fmt", "yuv420p",
        "-c:a", "aac", "-b:a", "192k",
        "-shortest", "-vf", "scale=1080:1920",
        "-movflags", "+faststart",
        outFile.getFullPathName()
    };
    juce::ChildProcess proc;
    return proc.start(args) && proc.waitForProcessToFinish(120000) == 0;
}
