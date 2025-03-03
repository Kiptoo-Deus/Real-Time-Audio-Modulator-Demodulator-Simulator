# Real-Time Audio Modulator/Demodulator Simulator
A C++ tool simulating AM/FM radio transmission with real-time audio processing and noise.

## Features
- Modulates live audio into AM or FM signals.
- Adds Gaussian noise to mimic a comms channel.
- Demodulates back to playable audio.
- Switch modes live: 'A' for AM, 'F' for FM, 'Q' to quit.

## Build (Windows with MSYS2)
1. Install MSYS2 from msys2.org, open MinGW 64-bit terminal.
2. Update: `pacman -Syu` (run twice if prompted).
3. Install tools: `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-portaudio`.
4. Navigate to project: `cd /c/path/to/AudioModulator`.
5. Build: `mkdir build && cd build && cmake -G "MSYS Makefiles" .. && make`.

## Run
- Start: `./modulator.exe`
- Controls: Press 'A' for AM, 'F' for FM, 'Q' to quit.

