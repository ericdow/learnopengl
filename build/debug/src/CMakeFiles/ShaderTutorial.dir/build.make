# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ericdow/code/learnopengl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ericdow/code/learnopengl/build/debug

# Include any dependencies generated for this target.
include src/CMakeFiles/ShaderTutorial.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/ShaderTutorial.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/ShaderTutorial.dir/flags.make

src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o: src/CMakeFiles/ShaderTutorial.dir/flags.make
src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o: ../../src/ShaderTutorial.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ericdow/code/learnopengl/build/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o"
	cd /home/ericdow/code/learnopengl/build/debug/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o -c /home/ericdow/code/learnopengl/src/ShaderTutorial.cpp

src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.i"
	cd /home/ericdow/code/learnopengl/build/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ericdow/code/learnopengl/src/ShaderTutorial.cpp > CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.i

src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.s"
	cd /home/ericdow/code/learnopengl/build/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ericdow/code/learnopengl/src/ShaderTutorial.cpp -o CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.s

src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o.requires:

.PHONY : src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o.requires

src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o.provides: src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/ShaderTutorial.dir/build.make src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o.provides.build
.PHONY : src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o.provides

src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o.provides.build: src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o


# Object files for target ShaderTutorial
ShaderTutorial_OBJECTS = \
"CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o"

# External object files for target ShaderTutorial
ShaderTutorial_EXTERNAL_OBJECTS =

src/ShaderTutorial: src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o
src/ShaderTutorial: src/CMakeFiles/ShaderTutorial.dir/build.make
src/ShaderTutorial: /usr/lib/x86_64-linux-gnu/libGLU.so
src/ShaderTutorial: /usr/lib/x86_64-linux-gnu/libGL.so
src/ShaderTutorial: /usr/lib/x86_64-linux-gnu/libglut.so
src/ShaderTutorial: /usr/lib/x86_64-linux-gnu/libXmu.so
src/ShaderTutorial: /usr/lib/x86_64-linux-gnu/libXi.so
src/ShaderTutorial: /usr/lib/x86_64-linux-gnu/libGLEW.so
src/ShaderTutorial: /usr/lib/libSOIL.so
src/ShaderTutorial: ../../lib/libassimp.so
src/ShaderTutorial: src/CMakeFiles/ShaderTutorial.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ericdow/code/learnopengl/build/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ShaderTutorial"
	cd /home/ericdow/code/learnopengl/build/debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ShaderTutorial.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/ShaderTutorial.dir/build: src/ShaderTutorial

.PHONY : src/CMakeFiles/ShaderTutorial.dir/build

src/CMakeFiles/ShaderTutorial.dir/requires: src/CMakeFiles/ShaderTutorial.dir/ShaderTutorial.cpp.o.requires

.PHONY : src/CMakeFiles/ShaderTutorial.dir/requires

src/CMakeFiles/ShaderTutorial.dir/clean:
	cd /home/ericdow/code/learnopengl/build/debug/src && $(CMAKE_COMMAND) -P CMakeFiles/ShaderTutorial.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/ShaderTutorial.dir/clean

src/CMakeFiles/ShaderTutorial.dir/depend:
	cd /home/ericdow/code/learnopengl/build/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ericdow/code/learnopengl /home/ericdow/code/learnopengl/src /home/ericdow/code/learnopengl/build/debug /home/ericdow/code/learnopengl/build/debug/src /home/ericdow/code/learnopengl/build/debug/src/CMakeFiles/ShaderTutorial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/ShaderTutorial.dir/depend

