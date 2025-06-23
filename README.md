# Prism VST Plugin

This repository contains a minimal example of a VST-style audio plugin. The plugin simply copies the input buffer to the output buffer.

## Dependencies

- [CMake](https://cmake.org/) 3.5 or newer
- A C++ compiler with C++11 support such as **g++**, **clang++** or **MSVC**

These tools are typically available through your system's package manager. On Ubuntu, for example:

```bash
sudo apt-get install build-essential cmake
```

With the prerequisites installed you can build the plugin as follows.

## Building

Run the following commands from the repository root:

```bash
mkdir build
cd build
cmake ..
make
```

The shared library `PrismVSTPlugin.so` will appear in the `build` directory. Copy this file to your DAW's plug‑in folder or load it directly in a compatible host application.

## Running the example host

A small test program is built alongside the plugin. From the `build` directory run:

```bash
./PluginHost
```

The host loads `PrismVSTPlugin.so`, feeds dummy audio data through the plugin and verifies the output matches the input.

## Version control setup

To associate this repository with a remote location (e.g. GitHub) run:

```bash
git remote add origin https://github.com/<your-user>/Prism-VST-Plugin.git
git push -u origin main
```

Replace the URL with your own repository location. This enables easier
collaboration and backup.


## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines on how to propose changes.

## License

This project is licensed under the [MIT License](LICENSE).
