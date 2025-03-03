#include <portaudio.h>
#include <iostream>
#include <cmath>
#define SAMPLE_RATE 44100
#define BUFFER_SIZE 256

PaStream* stream;
float carrier_freq = 10000.0f; // 10 kHz
float carrier_time = 0.0f;     

float carrier(float amplitude) {
    carrier_time += 1.0f / SAMPLE_RATE;
    return amplitude * sinf(2 * M_PI * carrier_freq * carrier_time);
}

static int audioCallback(const void* input, void* output, unsigned long frameCount,
                         const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void*) {
    const float* in = (const float*)input;
    float* out = (float*)output;
    for (unsigned long i = 0; i < frameCount; i++) {
        out[i] = in[i] * carrier(1.0f); // AM modulation
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
    std::cout << "Running... Press Enter to stop\n";
    std::cin.get();
    Pa_StopStream(stream);
    Pa_Terminate();
    return 0;
}