# Real-Time Audio Modulator/Demodulator Simulator
A C++ tool simulating AM/FM radio transmission with real-time audio processing and GUI.

## Features
- Modulates live audio into AM/FM signals via Qt GUI.
- Adds adjustable Gaussian noise and echo effect.
- Demodulates with real-time waveform and spectrum visualization (QCustomPlot, FFTW).
- Records output to WAV file.
- Controls: AM/FM buttons, noise slider, record/echo toggles.

## Build (Windows with MSYS2)
1. Install MSYS2 (msys2.org), update: `pacman -Syu`.
2. Install: `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-portaudio mingw-w64-x86_64-qt5 mingw-w64-x86_64-libsndfile mingw-w64-x86_64-fftw`.
3. Add qcustomplot.h and qcustomplot.cpp to project folder.
4. `cd /c/path/to/AudioModulator`
5. `mkdir build && cd build && cmake -G "MSYS Makefiles" .. && make`

## Run
- `./modulator.exe`

![image](https://github.com/user-attachments/assets/4eec2aea-29d4-4bd5-ad4b-a321f8f7d19d)
