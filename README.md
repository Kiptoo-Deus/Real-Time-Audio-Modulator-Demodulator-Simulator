# Real-Time Audio Modulator/Demodulator Simulator
A C++ tool simulating AM/FM radio transmission with real-time audio processing and GUI.

## Features
- Modulates live audio into AM or FM signals via Qt GUI.
- Adds adjustable Gaussian noise.
- Demodulates with real-time waveform visualization (QCustomPlot).
- Records output to WAV file.
- Controls: AM/FM buttons, noise slider, record toggle.

## Build (Windows with MSYS2)
1. Install MSYS2 (msys2.org), update: `pacman -Syu`.
2. Install: `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-portaudio mingw-w64-x86_64-qt5 mingw-w64-x86_64-libsndfile`.
3. Add qcustomplot.h and qcustomplot.cpp to project folder.
4. `cd /c/path/to/AudioModulator`
5. `mkdir build && cd build && cmake -G "MSYS Makefiles" .. && make`

## Run
- `./modulator.exe`

## Demo
[See demo.mp4]