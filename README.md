# Prism VST Plugin

Prism is a lightweight example project demonstrating the basic structure of a VST-style audio plug-in. The code is intentionally minimal so developers can understand the pieces required to compile a shared library that processes audio. The sample processor simply copies its input buffer to the output buffer.

## Project layout

- **include** – public header files for the plug-in interface
- **src** – implementation of the example processor
- **tests** – a small host program that loads the plug-in for verification
- **CMakeLists.txt** – build configuration for both the plug-in and the test host

## Downloading a release

Prebuilt binaries will be provided on the project website. Download the archive
for your operating system and follow the installation instructions below. The
installer script copies the plug‑in to the standard VST3 directory so it can be
loaded by any DAW on your machine.

## Building the plug-in

Prerequisites:

- [CMake](https://cmake.org/) 3.5 or newer
- A C++11 compatible compiler such as **g++**, **clang++** or **MSVC**

Install the tools through your platform's package manager. On Ubuntu:

```bash
sudo apt-get install build-essential cmake
```

Compile everything in a separate build directory:

```bash
mkdir build
cd build
cmake ..
make
```

The library `PrismVSTPlugin.so` will be created inside `build/`. Copy it to your
DAW's plug‑in folder or reference the path directly from compatible host
software.

### Creating installable packages

After building you can generate a redistributable archive with:

```bash
cmake --build . --target package
```

This produces `PrismVSTPlugin-0.1.0-<platform>.zip` containing the plug‑in
ready for installation.

### Installing the plug‑in

Extract the archive and run the helper script:

```bash
./scripts/install_plugin.sh
```

The script copies the library to the standard VST3 directory for each OS:

- **Windows** – `C:/Program Files/Common Files/VST3`
- **macOS** – `/Library/Audio/Plug-Ins/VST3`
- **Linux** – `~/.vst3`

Once installed, any compatible DAW should automatically find the plug‑in.

## Running the example host

The build also produces a `PluginHost` executable. From the `build` folder run:

```bash
./PluginHost
```

`PluginHost` loads `PrismVSTPlugin.so`, runs dummy audio through the `process` function and checks that the output matches the input. This helps verify that the plug-in can be loaded by external applications.

## Version control

If you wish to push your changes to a remote repository run:

```bash
git remote add origin https://github.com/<your-user>/Prism-VST-Plugin.git
git push -u origin main
```

Replace the URL with your own. Using a remote enables collaboration and acts as a backup.

## Contributing

Contributions are welcome! See [CONTRIBUTING.md](CONTRIBUTING.md) for instructions on how to propose improvements or new features.

## License

This project is released under the [MIT License](LICENSE).
