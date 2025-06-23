#ifndef PRISM_PLUGIN_H
#define PRISM_PLUGIN_H

class PrismPlugin {
public:
    PrismPlugin();
    void process(float* input, float* output, int numSamples);
};

extern "C" {
    PrismPlugin* createPlugin();
    void process(PrismPlugin* plugin, float* input, float* output, int numSamples);
    void destroyPlugin(PrismPlugin* plugin);
}

#endif // PRISM_PLUGIN_H
