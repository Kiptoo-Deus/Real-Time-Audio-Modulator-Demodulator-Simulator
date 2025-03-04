#include <portaudio.h>
#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>
#include "qcustomplot.h"
#include <sndfile.h>
#include <fftw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#define SAMPLE_RATE 44100
#define BUFFER_SIZE 256
#define ECHO_DELAY (SAMPLE_RATE / 4) // 0.25s delay

PaStream* stream;
float carrier_freq = 10000.0f;
float carrier_time = 0.0f;
float phase = 0.0f;
float last_sample = 0.0f;
std::vector<float> modulated(BUFFER_SIZE);
std::vector<float> demodulated(BUFFER_SIZE);
float lowpass_state = 0.0f;
std::string mode = "AM";
float noise_level = 0.1f;
std::random_device rd;
std::mt19937 gen(rd());
std::normal_distribution<float> noise(0.0f, noise_level);
SNDFILE* wav_file = nullptr;
SF_INFO sf_info = {0};
bool is_recording = false;
std::vector<float> echo_buffer(ECHO_DELAY, 0.0f); // Echo delay line
size_t echo_pos = 0;
bool echo_enabled = false; // Echo state

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
    return sample + noise(gen);
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
        if (echo_enabled) { // Apply echo
            float delayed = echo_buffer[echo_pos];
            demodulated[i] = demodulated[i] + 0.5f * delayed; // Mix with 50% echo
            echo_buffer[echo_pos] = demodulated[i]; // Update delay line
            echo_pos = (echo_pos + 1) % ECHO_DELAY;
        }
        out[i] = demodulated[i];
    }
    if (is_recording && wav_file) {
        sf_write_float(wav_file, demodulated.data(), frameCount);
    }
    return paContinue;
}

void initAudio() {
    Pa_Initialize();
    Pa_OpenDefaultStream(&stream, 1, 1, paFloat32, SAMPLE_RATE, BUFFER_SIZE, audioCallback, nullptr);
    Pa_StartStream(stream);
}

void cleanupAudio() {
    if (stream) {
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
        Pa_Terminate();
    }
    if (wav_file) {
        sf_close(wav_file);
        wav_file = nullptr;
    }
}

class AudioWindow : public QWidget {
    Q_OBJECT
public:
    AudioWindow(QWidget* parent = nullptr) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout(this);
        QPushButton* amButton = new QPushButton("AM Mode", this);
        QPushButton* fmButton = new QPushButton("FM Mode", this);
        QSlider* noiseSlider = new QSlider(Qt::Horizontal, this);
        noiseSlider->setRange(0, 50);
        noiseSlider->setValue(10);
        recordButton = new QPushButton("Start Recording", this);
        echoButton = new QPushButton("Enable Echo", this); // New echo button
        waveformPlot = new QCustomPlot(this);
        waveformPlot->addGraph();
        waveformPlot->xAxis->setRange(0, BUFFER_SIZE);
        waveformPlot->yAxis->setRange(-1, 1);
        waveformPlot->setMinimumHeight(200);
        spectrumPlot = new QCustomPlot(this);
        spectrumPlot->addGraph();
        spectrumPlot->xAxis->setRange(0, SAMPLE_RATE / 2);
        spectrumPlot->yAxis->setRange(0, 1);
        spectrumPlot->setMinimumHeight(200);

        layout->addWidget(amButton);
        layout->addWidget(fmButton);
        layout->addWidget(noiseSlider);
        layout->addWidget(recordButton);
        layout->addWidget(echoButton);
        layout->addWidget(waveformPlot);
        layout->addWidget(spectrumPlot);
        setLayout(layout);

        connect(amButton, &QPushButton::clicked, this, &AudioWindow::setAM);
        connect(fmButton, &QPushButton::clicked, this, &AudioWindow::setFM);
        connect(noiseSlider, &QSlider::valueChanged, this, &AudioWindow::setNoise);
        connect(recordButton, &QPushButton::clicked, this, &AudioWindow::toggleRecord);
        connect(echoButton, &QPushButton::clicked, this, &AudioWindow::toggleEcho);

        QTimer* timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &AudioWindow::updatePlots);
        timer->start(50);

        sf_info.channels = 1;
        sf_info.samplerate = SAMPLE_RATE;
        sf_info.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;

        fft_in = (double*)fftw_malloc(sizeof(double) * BUFFER_SIZE);
        fft_out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * (BUFFER_SIZE / 2 + 1));
        fft_plan = fftw_plan_dft_r2c_1d(BUFFER_SIZE, fft_in, fft_out, FFTW_ESTIMATE);
    }
    ~AudioWindow() {
        fftw_destroy_plan(fft_plan);
        fftw_free(fft_in);
        fftw_free(fft_out);
        cleanupAudio();
    }

private slots:
    void setAM() { mode = "AM"; std::cout << "Switched to AM\n"; }
    void setFM() { mode = "FM"; std::cout << "Switched to FM\n"; }
    void setNoise(int value) { 
        noise_level = value / 100.0f; 
        noise = std::normal_distribution<float>(0.0f, noise_level); 
        std::cout << "Noise level set to " << noise_level << "\n";
    }
    void toggleRecord() {
        if (!is_recording) {
            wav_file = sf_open("output.wav", SFM_WRITE, &sf_info);
            if (!wav_file) {
                std::cout << "Failed to open output.wav: " << sf_strerror(nullptr) << "\n";
                return;
            }
            is_recording = true;
            recordButton->setText("Stop Recording");
            std::cout << "Recording started\n";
        } else {
            sf_close(wav_file);
            wav_file = nullptr;
            is_recording = false;
            recordButton->setText("Start Recording");
            std::cout << "Recording stopped\n";
        }
    }
    void toggleEcho() {
        echo_enabled = !echo_enabled;
        echoButton->setText(echo_enabled ? "Disable Echo" : "Enable Echo");
        std::cout << (echo_enabled ? "Echo enabled\n" : "Echo disabled\n");
    }
    void updatePlots() {
        QVector<double> x(BUFFER_SIZE), y(BUFFER_SIZE);
        for (int i = 0; i < BUFFER_SIZE; i++) {
            x[i] = i;
            y[i] = demodulated[i];
        }
        waveformPlot->graph(0)->setData(x, y);
        waveformPlot->replot();

        for (int i = 0; i < BUFFER_SIZE; i++) {
            fft_in[i] = demodulated[i];
        }
        fftw_execute(fft_plan);
        QVector<double> freq(BUFFER_SIZE / 2), mag(BUFFER_SIZE / 2);
        for (int i = 0; i < BUFFER_SIZE / 2; i++) {
            freq[i] = i * SAMPLE_RATE / BUFFER_SIZE;
            mag[i] = sqrt(fft_out[i][0] * fft_out[i][0] + fft_out[i][1] * fft_out[i][1]) / BUFFER_SIZE;
        }
        spectrumPlot->graph(0)->setData(freq, mag);
        spectrumPlot->replot();
    }

private:
    QCustomPlot* waveformPlot;
    QCustomPlot* spectrumPlot;
    QPushButton* recordButton;
    QPushButton* echoButton; 
    double* fft_in;
    fftw_complex* fft_out;
    fftw_plan fft_plan;
};

int main(int argc, char* argv[]) {
    initAudio();
    QApplication app(argc, argv);
    AudioWindow window;
    window.show();
    int result = app.exec();
    cleanupAudio();
    return result;
}

#include "main.moc"