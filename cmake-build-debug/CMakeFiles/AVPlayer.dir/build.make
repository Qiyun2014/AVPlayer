# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/qiyun/AVPlayer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/qiyun/AVPlayer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AVPlayer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AVPlayer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AVPlayer.dir/flags.make

CMakeFiles/AVPlayer.dir/main.cpp.o: CMakeFiles/AVPlayer.dir/flags.make
CMakeFiles/AVPlayer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/qiyun/AVPlayer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AVPlayer.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AVPlayer.dir/main.cpp.o -c /Users/qiyun/AVPlayer/main.cpp

CMakeFiles/AVPlayer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AVPlayer.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/qiyun/AVPlayer/main.cpp > CMakeFiles/AVPlayer.dir/main.cpp.i

CMakeFiles/AVPlayer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AVPlayer.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/qiyun/AVPlayer/main.cpp -o CMakeFiles/AVPlayer.dir/main.cpp.s

CMakeFiles/AVPlayer.dir/Decoder/MediaParser.cpp.o: CMakeFiles/AVPlayer.dir/flags.make
CMakeFiles/AVPlayer.dir/Decoder/MediaParser.cpp.o: ../Decoder/MediaParser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/qiyun/AVPlayer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AVPlayer.dir/Decoder/MediaParser.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AVPlayer.dir/Decoder/MediaParser.cpp.o -c /Users/qiyun/AVPlayer/Decoder/MediaParser.cpp

CMakeFiles/AVPlayer.dir/Decoder/MediaParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AVPlayer.dir/Decoder/MediaParser.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/qiyun/AVPlayer/Decoder/MediaParser.cpp > CMakeFiles/AVPlayer.dir/Decoder/MediaParser.cpp.i

CMakeFiles/AVPlayer.dir/Decoder/MediaParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AVPlayer.dir/Decoder/MediaParser.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/qiyun/AVPlayer/Decoder/MediaParser.cpp -o CMakeFiles/AVPlayer.dir/Decoder/MediaParser.cpp.s

CMakeFiles/AVPlayer.dir/MessageQueue/DataBufferQueue.cpp.o: CMakeFiles/AVPlayer.dir/flags.make
CMakeFiles/AVPlayer.dir/MessageQueue/DataBufferQueue.cpp.o: ../MessageQueue/DataBufferQueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/qiyun/AVPlayer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/AVPlayer.dir/MessageQueue/DataBufferQueue.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AVPlayer.dir/MessageQueue/DataBufferQueue.cpp.o -c /Users/qiyun/AVPlayer/MessageQueue/DataBufferQueue.cpp

CMakeFiles/AVPlayer.dir/MessageQueue/DataBufferQueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AVPlayer.dir/MessageQueue/DataBufferQueue.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/qiyun/AVPlayer/MessageQueue/DataBufferQueue.cpp > CMakeFiles/AVPlayer.dir/MessageQueue/DataBufferQueue.cpp.i

CMakeFiles/AVPlayer.dir/MessageQueue/DataBufferQueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AVPlayer.dir/MessageQueue/DataBufferQueue.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/qiyun/AVPlayer/MessageQueue/DataBufferQueue.cpp -o CMakeFiles/AVPlayer.dir/MessageQueue/DataBufferQueue.cpp.s

CMakeFiles/AVPlayer.dir/Decoder/MediaDecoder.cpp.o: CMakeFiles/AVPlayer.dir/flags.make
CMakeFiles/AVPlayer.dir/Decoder/MediaDecoder.cpp.o: ../Decoder/MediaDecoder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/qiyun/AVPlayer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/AVPlayer.dir/Decoder/MediaDecoder.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AVPlayer.dir/Decoder/MediaDecoder.cpp.o -c /Users/qiyun/AVPlayer/Decoder/MediaDecoder.cpp

CMakeFiles/AVPlayer.dir/Decoder/MediaDecoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AVPlayer.dir/Decoder/MediaDecoder.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/qiyun/AVPlayer/Decoder/MediaDecoder.cpp > CMakeFiles/AVPlayer.dir/Decoder/MediaDecoder.cpp.i

CMakeFiles/AVPlayer.dir/Decoder/MediaDecoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AVPlayer.dir/Decoder/MediaDecoder.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/qiyun/AVPlayer/Decoder/MediaDecoder.cpp -o CMakeFiles/AVPlayer.dir/Decoder/MediaDecoder.cpp.s

CMakeFiles/AVPlayer.dir/Decoder/Render/SDLRender.cpp.o: CMakeFiles/AVPlayer.dir/flags.make
CMakeFiles/AVPlayer.dir/Decoder/Render/SDLRender.cpp.o: ../Decoder/Render/SDLRender.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/qiyun/AVPlayer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/AVPlayer.dir/Decoder/Render/SDLRender.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AVPlayer.dir/Decoder/Render/SDLRender.cpp.o -c /Users/qiyun/AVPlayer/Decoder/Render/SDLRender.cpp

CMakeFiles/AVPlayer.dir/Decoder/Render/SDLRender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AVPlayer.dir/Decoder/Render/SDLRender.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/qiyun/AVPlayer/Decoder/Render/SDLRender.cpp > CMakeFiles/AVPlayer.dir/Decoder/Render/SDLRender.cpp.i

CMakeFiles/AVPlayer.dir/Decoder/Render/SDLRender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AVPlayer.dir/Decoder/Render/SDLRender.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/qiyun/AVPlayer/Decoder/Render/SDLRender.cpp -o CMakeFiles/AVPlayer.dir/Decoder/Render/SDLRender.cpp.s

CMakeFiles/AVPlayer.dir/Utility/AVTimer.cpp.o: CMakeFiles/AVPlayer.dir/flags.make
CMakeFiles/AVPlayer.dir/Utility/AVTimer.cpp.o: ../Utility/AVTimer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/qiyun/AVPlayer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/AVPlayer.dir/Utility/AVTimer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AVPlayer.dir/Utility/AVTimer.cpp.o -c /Users/qiyun/AVPlayer/Utility/AVTimer.cpp

CMakeFiles/AVPlayer.dir/Utility/AVTimer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AVPlayer.dir/Utility/AVTimer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/qiyun/AVPlayer/Utility/AVTimer.cpp > CMakeFiles/AVPlayer.dir/Utility/AVTimer.cpp.i

CMakeFiles/AVPlayer.dir/Utility/AVTimer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AVPlayer.dir/Utility/AVTimer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/qiyun/AVPlayer/Utility/AVTimer.cpp -o CMakeFiles/AVPlayer.dir/Utility/AVTimer.cpp.s

# Object files for target AVPlayer
AVPlayer_OBJECTS = \
"CMakeFiles/AVPlayer.dir/main.cpp.o" \
"CMakeFiles/AVPlayer.dir/Decoder/MediaParser.cpp.o" \
"CMakeFiles/AVPlayer.dir/MessageQueue/DataBufferQueue.cpp.o" \
"CMakeFiles/AVPlayer.dir/Decoder/MediaDecoder.cpp.o" \
"CMakeFiles/AVPlayer.dir/Decoder/Render/SDLRender.cpp.o" \
"CMakeFiles/AVPlayer.dir/Utility/AVTimer.cpp.o"

# External object files for target AVPlayer
AVPlayer_EXTERNAL_OBJECTS =

AVPlayer: CMakeFiles/AVPlayer.dir/main.cpp.o
AVPlayer: CMakeFiles/AVPlayer.dir/Decoder/MediaParser.cpp.o
AVPlayer: CMakeFiles/AVPlayer.dir/MessageQueue/DataBufferQueue.cpp.o
AVPlayer: CMakeFiles/AVPlayer.dir/Decoder/MediaDecoder.cpp.o
AVPlayer: CMakeFiles/AVPlayer.dir/Decoder/Render/SDLRender.cpp.o
AVPlayer: CMakeFiles/AVPlayer.dir/Utility/AVTimer.cpp.o
AVPlayer: CMakeFiles/AVPlayer.dir/build.make
AVPlayer: CMakeFiles/AVPlayer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/qiyun/AVPlayer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable AVPlayer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AVPlayer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AVPlayer.dir/build: AVPlayer

.PHONY : CMakeFiles/AVPlayer.dir/build

CMakeFiles/AVPlayer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AVPlayer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AVPlayer.dir/clean

CMakeFiles/AVPlayer.dir/depend:
	cd /Users/qiyun/AVPlayer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/qiyun/AVPlayer /Users/qiyun/AVPlayer /Users/qiyun/AVPlayer/cmake-build-debug /Users/qiyun/AVPlayer/cmake-build-debug /Users/qiyun/AVPlayer/cmake-build-debug/CMakeFiles/AVPlayer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AVPlayer.dir/depend

