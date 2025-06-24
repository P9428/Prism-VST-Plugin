# Prism VST Plugin

This repository contains a JUCE-based VST3/AU plugin that lets creators publish audio directly to TikTok. It provides a real-time processing pipeline, OAuth authentication and automatic rights checking.

## Features

- **Cross-platform:** Built with JUCE and CMake for macOS and Windows.
- **Loudness processing:** Real-time limiting and normalization to -14 LUFS.
- **TikTok integration:** OAuth authentication and chunked upload workflow.
- **Automated rights check:** Verification using the ACRCloud API.

## Building

1. Install the [JUCE](https://juce.com/get-juce) library and ensure the `JUCE` folder is located next to this repository (`/workspace/Prism-VST-Plugin/JUCE`).
2. Install [FFMpeg](https://ffmpeg.org/) and make sure the `ffmpeg` executable is in your PATH.
3. Create a build directory and run CMake:

```bash
mkdir build && cd build
cmake .. -B . -G "Unix Makefiles"
cmake --build . --config Release
```

The resulting plugin will be located in the `build` directory.

Before building, define the following environment variables for your API credentials:

```
export TIKTOK_CLIENT_ID=your_client_id
export TIKTOK_CLIENT_SECRET=your_client_secret
export ACRCLOUD_TOKEN=your_acr_token
```

## Usage

Open the built plugin in a supported DAW (Ableton Live, FL Studio, Logic Pro). When loaded, the plugin processes audio in real time and prepares it for upload to TikTok.

1. Load the plugin on a stereo track.
2. Press the "Share" button in the UI to start authentication and upload.
3. Follow the browser flow to grant TikTok permissions.


## Notes

The plugin requires valid TikTok and ACRCloud credentials. Set the environment variables as described above before building.
