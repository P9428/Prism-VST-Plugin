# Prism-VST-Plugin

This repository contains a JUCE-based audio plug-in named *Prism*.

## Build

1. Download the JUCE framework separately. The source must be placed in a
   directory named `JUCE` located next to this repository (i.e. `../JUCE`),
   or add JUCE as a git submodule at that location.
2. Prism currently requires **JUCE 7 or later**.
3. Configure the project with CMake. You can optionally specify the path to JUCE
   using the `JUCE_DIR` option:

```bash
cmake -S . -B build -D JUCE_DIR=/path/to/JUCE
cmake --build build
```

If `JUCE_DIR` is not provided, CMake will look for JUCE in `../JUCE` by
default.
