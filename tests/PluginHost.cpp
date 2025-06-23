#include <iostream>
#if defined(_WIN32)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

using CreateFunc = void* (*)();
using ProcessFunc = void (*)(void*, float*, float*, int);
using DestroyFunc = void (*)(void*);

int main() {
#if defined(_WIN32)
    const char* libName = "PrismVSTPlugin.dll";
    HMODULE handle = LoadLibraryA(libName);
    if (!handle) {
        std::cerr << "Failed to load plugin" << std::endl;
        return 1;
    }
    auto create = reinterpret_cast<CreateFunc>(GetProcAddress(handle, "createPlugin"));
    auto process = reinterpret_cast<ProcessFunc>(GetProcAddress(handle, "process"));
    auto destroy = reinterpret_cast<DestroyFunc>(GetProcAddress(handle, "destroyPlugin"));
#else
    const char* libName = "./PrismVSTPlugin.so";
    void* handle = dlopen(libName, RTLD_LAZY);
    if (!handle) {
        std::cerr << "Failed to load plugin: " << dlerror() << std::endl;
        return 1;
    }
    auto create = reinterpret_cast<CreateFunc>(dlsym(handle, "createPlugin"));
    auto process = reinterpret_cast<ProcessFunc>(dlsym(handle, "process"));
    auto destroy = reinterpret_cast<DestroyFunc>(dlsym(handle, "destroyPlugin"));
#endif

    if (!create || !process || !destroy) {
        std::cerr << "Missing symbol" << std::endl;
#if defined(_WIN32)
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif
        return 1;
    }

    void* plugin = create();

    const int numSamples = 64;
    float input[numSamples];
    float output[numSamples];

    for (int i = 0; i < numSamples; ++i) {
        input[i] = static_cast<float>(i);
        output[i] = 0.0f;
    }

    process(plugin, input, output, numSamples);

    bool success = true;
    for (int i = 0; i < numSamples; ++i) {
        if (input[i] != output[i]) {
            std::cerr << "Mismatch at sample " << i << std::endl;
            success = false;
            break;
        }
    }

    destroy(plugin);
#if defined(_WIN32)
    FreeLibrary(handle);
#else
    dlclose(handle);
#endif

    if (success) {
        std::cout << "Plugin processed successfully." << std::endl;
        return 0;
    }
    return 1;
}
