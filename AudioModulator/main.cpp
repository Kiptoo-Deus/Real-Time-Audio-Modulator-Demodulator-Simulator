#include <portaudio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <conio.h> 
#include <random>  // For noise generation
#define SAMPLE_RATE 44100
#define BUFFER_SIZE 256

PaStream* stream;
float carrier_freq = 10000.0f;
float carrier_time = 0.0f;
float phase = 0.0f;
float last_sample = 0.0f;
std::vector<float> modulated(BUFFER_SIZE);
std::vector<float> demodulated(BUFFER_SIZE);
float lowpass_state = 0.0f;
std::string mode = "AM";
std::random_device rd;
std::mt19937 gen(rd());
std::normal_distribution<float> noise(0.0f, 0.1f); // Mean 0, small variance

float carrier(float amplitude) {
    carrier_time += 1.0f / SAMPLE_RATE;
    return amplitude * sinf(2 * M_PI * carrier_freq * carrier_time);
}

float modulateAM(float audio_sample) {
    return (1.0f + audio_sample) * carrier(0.5f);
}

float modulateFM(float audio_sample) {
    float freq_dev = 5000.0f;
    phase += 2 * M_PI * (carrier_freq + audio_sample * freq_dev) / SAMPLE_RATE;
    return sinf(phase);
}

float addNoise(float sample) {
    return sample + noise(gen); // Add Gaussian noise
}

void demodAM(const std::vector<float>& in, std::vector<float>& out) {
    const float alpha = 0.01f;
    for (size_t i = 0; i < in.size(); i++) {
        float rectified = fabs(in[i]);
        lowpass_state = lowpass_state + alpha * (rectified - lowpass_state);
        out[i] = lowpass_state - 0.5f;
    }
}

void demodFM(const std::vector<float>& in, std::vector<float>& out) {
    for (size_t i = 0; i < in.size(); i++) {
        out[i] = (in[i] * last_sample) * SAMPLE_RATE;
        last_sample = in[i];
    }
}

static int audioCallback(const void* input, void* output, unsigned long frameCount,
                         const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void*) {
    const float* in = (const float*)input;
    float* out = (float*)output;
    for (unsigned long i = 0; i < frameCount; i++) {
        modulated[i] = (mode == "FM") ? modulateFM(in[i]) : modulateAM(in[i]);
        modulated[i] = addNoise(modulated[i]); 
        if (mode == "FM") demodFM(modulated, demodulated);
        else demodAM(modulated, demodulated);
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
    std::cout << "Running (A for AM, F for FM, Q to quit)...\n";
    while (true) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 'a' || key == 'A') {
                mode = "AM";
                std::cout << "Switched to AM\n";
            }
            else if (key == 'f' || key == 'F') {
                mode = "FM";
                std::cout << "Switched to FM\n";
            }
            else if (key == 'q' || key == 'Q') {
                std::cout << "Quitting...\n";
                break;
            }
        }
    }
    Pa_StopStream(stream);
    Pa_Terminate();
    return 0;
}