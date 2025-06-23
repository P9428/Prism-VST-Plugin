# Prism VST Plugin

Prism is a lightweight example project demonstrating the basic structure of a
VST‑style audio plug‑in. The focus is on simplicity and speed so the binary can
be dropped into any DAW and just work. The sample processor simply copies its
input buffer to the output buffer, providing a stable starting point for your
own effects.

## Project layout

- **include** – public header files for the plug-in interface
- **src** – implementation of the example processor
- **tests** – a small host program that loads the plug-in for verification
- **CMakeLists.txt** – build configuration for both the plug-in and the test host

## Downloading a release

Prebuilt binaries will be provided on the project website. Simply download the
archive for your operating system and run the installer script described below.
It handles copying the plug‑in to the standard VST3 directory so any DAW can
pick it up without manual configuration.

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

Extract the archive and run the helper script from anywhere:

```bash
./scripts/install_plugin.sh
```

The script locates the build folder automatically and copies the library to the
standard VST3 directory for each OS:

- **Windows** – `C:/Program Files/Common Files/VST3`
- **macOS** – `/Library/Audio/Plug-Ins/VST3`
- **Linux** – `~/.vst3`

Once installed, any compatible DAW should automatically find the plug‑in. This
"one-click" installer ensures your producer friends can download the archive,
run the script, and start using Prism immediately.

## Running the example host

The build also produces a `PluginHost` executable. From the `build` folder run:

```bash
./PluginHost
```

`PluginHost` automatically selects the correct library extension for your OS,
loads the plugin, runs dummy audio through the `process` function and checks
that the output matches the input. This helps verify that the plug‑in can be
loaded by external applications.

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
