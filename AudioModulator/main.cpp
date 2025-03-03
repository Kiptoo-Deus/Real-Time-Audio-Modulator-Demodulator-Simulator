#include <portaudio.h>
#include <iostream>
#define SAMPLE_RATE 44100
#define BUFFER_SIZE 256

PaStream* stream;
float buffer[BUFFER_SIZE];

static int audioCallback(const void* input, void* output, unsigned long frameCount,
                         const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void*) {
    const float* in = (const float*)input;
    float* out = (float*)output;
    for (unsigned long i = 0; i < frameCount; i++) {
        out[i] = in[i]; // Passthrough
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