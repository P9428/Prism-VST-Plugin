# Prism VST Plugin

This repository contains a JUCE-based VST3/AU plugin that lets creators publish audio directly to TikTok. The implementation is a minimal MVP with placeholders where proprietary API logic would normally live.

## Features

- **Cross-platform:** Built with JUCE and CMake for macOS and Windows.
- **Loudness processing:** Placeholder real-time processor for limiting and normalization.
- **TikTok integration:** Placeholder OAuth and upload workflow.
- **Automated rights check:** Placeholder integration with an audio fingerprinting service.

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

- The TikTok API integration and rights checking components are placeholders. You must supply your own credentials and implementation.
- This code is for demonstration and requires further development for production use.
