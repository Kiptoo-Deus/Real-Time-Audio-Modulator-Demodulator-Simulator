cmake_minimum_required(VERSION 3.10)
project(AudioModulator)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON) # Enable MOC for Qt classes
set(CMAKE_AUTORCC ON) # Optional, for resources if added later
set(CMAKE_AUTOUIC ON) # Optional, for .ui files if added later

find_library(PORTAUDIO_LIB portaudio)
if(NOT PORTAUDIO_LIB)
    message(FATAL_ERROR "PortAudio not found. Ensure it's installed.")
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
if(NOT Qt5_FOUND)
    message(FATAL_ERROR "Qt5 Widgets not found. Install mingw-w64-x86_64-qt5.")
endif()

add_executable(modulator main.cpp)
target_link_libraries(modulator ${PORTAUDIO_LIB} Qt5::Widgets)