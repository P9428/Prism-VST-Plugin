# Prism VST Plugin

This repository contains the beginnings of a JUCE-based VST3/AU plugin that allows creators to publish audio directly to TikTok. The project is in an early MVP stage.

## Features

- **Cross-platform:** Built with JUCE and CMake for macOS and Windows.
- **Loudness processing:** Placeholder real-time processor for limiting and normalization.
- **TikTok integration:** Placeholder OAuth and upload workflow.
- **Automated rights check:** Placeholder integration with an audio fingerprinting service.

## Building

1. Install the [JUCE](https://juce.com/get-juce) library and ensure the `JUCE` folder is located next to this repository (`/workspace/Prism-VST-Plugin/JUCE`).
2. Create a build directory and run CMake:

```bash
mkdir build && cd build
cmake .. -B . -G "Unix Makefiles"
cmake --build . --config Release
```

The resulting plugin will be located in the `build` directory.

## Usage

Open the built plugin in a supported DAW (Ableton Live, FL Studio, Logic Pro). When loaded, the plugin processes audio in real time and prepares it for upload to TikTok.

## Notes

- The TikTok API integration and rights checking components are placeholders. You must supply your own credentials and implementation.
- This code is for demonstration and requires further development for production use.
