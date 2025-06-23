#include "PrismPlugin.h"

PrismPlugin::PrismPlugin() {}

void PrismPlugin::process(float* input, float* output, int numSamples) {
    for (int i = 0; i < numSamples; ++i) {
        output[i] = input[i];
    }
}

extern "C" {
PrismPlugin* createPlugin() {
    return new PrismPlugin();
}

void process(PrismPlugin* plugin, float* input, float* output, int numSamples) {
    plugin->process(input, output, numSamples);
}

void destroyPlugin(PrismPlugin* plugin) {
    delete plugin;
}
}
