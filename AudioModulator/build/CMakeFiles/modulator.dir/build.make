# CMAKE generated file: DO NOT EDIT!
# Generated by "MSYS Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /C/msys64/mingw64/bin/cmake.exe

# The command to remove a file.
RM = /C/msys64/mingw64/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/C/Users/JOEL/Documents/GitHub/Real Time Audio Modulator Demodulator Simulator/AudioModulator"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/C/Users/JOEL/Documents/GitHub/Real Time Audio Modulator Demodulator Simulator/AudioModulator/build"

# Include any dependencies generated for this target.
include CMakeFiles/modulator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/modulator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/modulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/modulator.dir/flags.make

CMakeFiles/modulator.dir/main.cpp.obj: CMakeFiles/modulator.dir/flags.make
CMakeFiles/modulator.dir/main.cpp.obj: C:/Users/JOEL/Documents/GitHub/Real\ Time\ Audio\ Modulator\ Demodulator\ Simulator/AudioModulator/main.cpp
CMakeFiles/modulator.dir/main.cpp.obj: CMakeFiles/modulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/C/Users/JOEL/Documents/GitHub/Real Time Audio Modulator Demodulator Simulator/AudioModulator/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/modulator.dir/main.cpp.obj"
	/C/msys64/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/modulator.dir/main.cpp.obj -MF CMakeFiles/modulator.dir/main.cpp.obj.d -o CMakeFiles/modulator.dir/main.cpp.obj -c "/C/Users/JOEL/Documents/GitHub/Real Time Audio Modulator Demodulator Simulator/AudioModulator/main.cpp"

CMakeFiles/modulator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/modulator.dir/main.cpp.i"
	/C/msys64/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/C/Users/JOEL/Documents/GitHub/Real Time Audio Modulator Demodulator Simulator/AudioModulator/main.cpp" > CMakeFiles/modulator.dir/main.cpp.i

CMakeFiles/modulator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/modulator.dir/main.cpp.s"
	/C/msys64/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/C/Users/JOEL/Documents/GitHub/Real Time Audio Modulator Demodulator Simulator/AudioModulator/main.cpp" -o CMakeFiles/modulator.dir/main.cpp.s

# Object files for target modulator
modulator_OBJECTS = \
"CMakeFiles/modulator.dir/main.cpp.obj"

# External object files for target modulator
modulator_EXTERNAL_OBJECTS =

modulator.exe: CMakeFiles/modulator.dir/main.cpp.obj
modulator.exe: CMakeFiles/modulator.dir/build.make
modulator.exe: C:/msys64/mingw64/lib/libportaudio.dll.a
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/C/Users/JOEL/Documents/GitHub/Real Time Audio Modulator Demodulator Simulator/AudioModulator/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable modulator.exe"
	/C/msys64/mingw64/bin/cmake.exe -E rm -f CMakeFiles/modulator.dir/objects.a
	/C/msys64/mingw64/bin/ar.exe qc CMakeFiles/modulator.dir/objects.a $(modulator_OBJECTS) $(modulator_EXTERNAL_OBJECTS)
	/C/msys64/mingw64/bin/c++.exe -Wl,--whole-archive CMakeFiles/modulator.dir/objects.a -Wl,--no-whole-archive -o modulator.exe -Wl,--out-implib,libmodulator.dll.a -Wl,--major-image-version,0,--minor-image-version,0  /C/msys64/mingw64/lib/libportaudio.dll.a -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32

# Rule to build all files generated by this target.
CMakeFiles/modulator.dir/build: modulator.exe
.PHONY : CMakeFiles/modulator.dir/build

CMakeFiles/modulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/modulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/modulator.dir/clean

CMakeFiles/modulator.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MSYS Makefiles" "/C/Users/JOEL/Documents/GitHub/Real Time Audio Modulator Demodulator Simulator/AudioModulator" "/C/Users/JOEL/Documents/GitHub/Real Time Audio Modulator Demodulator Simulator/AudioModulator" "/C/Users/JOEL/Documents/GitHub/Real Time Audio Modulator Demodulator Simulator/AudioModulator/build" "/C/Users/JOEL/Documents/GitHub/Real Time Audio Modulator Demodulator Simulator/AudioModulator/build" "/C/Users/JOEL/Documents/GitHub/Real Time Audio Modulator Demodulator Simulator/AudioModulator/build/CMakeFiles/modulator.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/modulator.dir/depend

