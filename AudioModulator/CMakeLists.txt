cmake_minimum_required(VERSION 3.10)
project(AudioModulator)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_library(PORTAUDIO_LIB portaudio)
if(NOT PORTAUDIO_LIB)
    message(FATAL_ERROR "PortAudio not found. Ensure it's installed.")
endif()

find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED) # Add PrintSupport
if(NOT Qt5_FOUND)
    message(FATAL_ERROR "Qt5 not found. Install mingw-w64-x86_64-qt5.")
endif()

add_executable(modulator main.cpp qcustomplot.cpp)
target_include_directories(modulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(modulator ${PORTAUDIO_LIB} Qt5::Widgets Qt5::PrintSupport) #I am Linking PrintSupport