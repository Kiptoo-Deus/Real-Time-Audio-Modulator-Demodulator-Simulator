cmake_minimum_required(VERSION 3.10)
project(AudioModulator)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_library(PORTAUDIO_LIB portaudio)
if(NOT PORTAUDIO_LIB)
    message(FATAL_ERROR "PortAudio not found.")
endif()

find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
if(NOT Qt5_FOUND)
    message(FATAL_ERROR "Qt5 not found. Install mingw-w64-x86_64-qt5.")
endif()

find_library(SNDFILE_LIB sndfile)
if(NOT SNDFILE_LIB)
    message(FATAL_ERROR "libsndfile not found. Install mingw-w64-x86_64-libsndfile.")
endif()

find_library(FFTW_LIB fftw3) # Add FFTW
if(NOT FFTW_LIB)
    message(FATAL_ERROR "FFTW not found. Install mingw-w64-x86_64-fftw.")
endif()

add_executable(modulator main.cpp qcustomplot.cpp)
target_include_directories(modulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(modulator ${PORTAUDIO_LIB} Qt5::Widgets Qt5::PrintSupport ${SNDFILE_LIB} ${FFTW_LIB})