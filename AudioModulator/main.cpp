#include <portaudio.h>
#include <iostream>
#include <cmath>
#include <vector>
#define SAMPLE_RATE 44100
#define BUFFER_SIZE 256

PaStream* stream;
float carrier_freq = 10000.0f;
float carrier_time = 0.0f;     
std::vector<float> modulated(BUFFER_SIZE);
std::vector<float> demodulated(BUFFER_SIZE);
float lowpass_state = 0.0f;

float carrier(float amplitude) {
    carrier_time += 1.0f / SAMPLE_RATE;
    return amplitude * sinf(2 * M_PI * carrier_freq * carrier_time);
}

float modulateAM(float audio_sample) {
    return (1.0f + audio_sample) * carrier(0.5f);
}

void demodAM(const std::vector<float>& in, std::vector<float>& out) {
    const float alpha = 0.01f;
    for (size_t i = 0; i < in.size(); i++) {
        float rectified = fabs(in[i]);
        lowpass_state = lowpass_state + alpha * (rectified - lowpass_state);
        out[i] = lowpass_state - 0.5f;
    }
}

static int audioCallback(const void* input, void* output, unsigned long frameCount,
                         const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void*) {
    const float* in = (const float*)input;
    float* out = (float*)output;
    for (unsigned long i = 0; i < frameCount; i++) {
        modulated[i] = modulateAM(in[i]);
        demodAM(modulated, demodulated);
        out[i] = demodulated[i];
    }
    return paContinue;
}

void initAudio() {
    Pa_Initialize();
    Pa_OpenDefaultStream(&stream, 1, 1, paFloat32, SAMPLE_RATE, BUFFER_SIZE, audioCallback, nullptr);
    Pa_StartStream(stream);
}

int main() {
    initAudio();
    std::cout << "Running AM... Press Enter to stop\n";
    std::cin.get();
    Pa_StopStream(stream);
    Pa_Terminate();
    return 0;
}