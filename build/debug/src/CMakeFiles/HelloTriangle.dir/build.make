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
include src/CMakeFiles/HelloTriangle.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/HelloTriangle.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/HelloTriangle.dir/flags.make

src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o: src/CMakeFiles/HelloTriangle.dir/flags.make
src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o: ../../src/HelloTriangle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ericdow/code/learnopengl/build/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o"
	cd /home/ericdow/code/learnopengl/build/debug/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o -c /home/ericdow/code/learnopengl/src/HelloTriangle.cpp

src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.i"
	cd /home/ericdow/code/learnopengl/build/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ericdow/code/learnopengl/src/HelloTriangle.cpp > CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.i

src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.s"
	cd /home/ericdow/code/learnopengl/build/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ericdow/code/learnopengl/src/HelloTriangle.cpp -o CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.s

src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o.requires:

.PHONY : src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o.requires

src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o.provides: src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/HelloTriangle.dir/build.make src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o.provides.build
.PHONY : src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o.provides

src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o.provides.build: src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o


# Object files for target HelloTriangle
HelloTriangle_OBJECTS = \
"CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o"

# External object files for target HelloTriangle
HelloTriangle_EXTERNAL_OBJECTS =

src/HelloTriangle: src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o
src/HelloTriangle: src/CMakeFiles/HelloTriangle.dir/build.make
src/HelloTriangle: /usr/lib/x86_64-linux-gnu/libGLU.so
src/HelloTriangle: /usr/lib/x86_64-linux-gnu/libGL.so
src/HelloTriangle: /usr/lib/x86_64-linux-gnu/libglut.so
src/HelloTriangle: /usr/lib/x86_64-linux-gnu/libXmu.so
src/HelloTriangle: /usr/lib/x86_64-linux-gnu/libXi.so
src/HelloTriangle: /usr/lib/x86_64-linux-gnu/libGLEW.so
src/HelloTriangle: /usr/lib/libSOIL.so
src/HelloTriangle: ../../lib/libassimp.so
src/HelloTriangle: src/CMakeFiles/HelloTriangle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ericdow/code/learnopengl/build/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HelloTriangle"
	cd /home/ericdow/code/learnopengl/build/debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HelloTriangle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/HelloTriangle.dir/build: src/HelloTriangle

.PHONY : src/CMakeFiles/HelloTriangle.dir/build

src/CMakeFiles/HelloTriangle.dir/requires: src/CMakeFiles/HelloTriangle.dir/HelloTriangle.cpp.o.requires

.PHONY : src/CMakeFiles/HelloTriangle.dir/requires

src/CMakeFiles/HelloTriangle.dir/clean:
	cd /home/ericdow/code/learnopengl/build/debug/src && $(CMAKE_COMMAND) -P CMakeFiles/HelloTriangle.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/HelloTriangle.dir/clean

src/CMakeFiles/HelloTriangle.dir/depend:
	cd /home/ericdow/code/learnopengl/build/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ericdow/code/learnopengl /home/ericdow/code/learnopengl/src /home/ericdow/code/learnopengl/build/debug /home/ericdow/code/learnopengl/build/debug/src /home/ericdow/code/learnopengl/build/debug/src/CMakeFiles/HelloTriangle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/HelloTriangle.dir/depend

