# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /home/sun/clion-2016.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/sun/clion-2016.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sun/MServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sun/MServer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MServer.dir/flags.make

CMakeFiles/MServer.dir/main.cpp.o: CMakeFiles/MServer.dir/flags.make
CMakeFiles/MServer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sun/MServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MServer.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MServer.dir/main.cpp.o -c /home/sun/MServer/main.cpp

CMakeFiles/MServer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MServer.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sun/MServer/main.cpp > CMakeFiles/MServer.dir/main.cpp.i

CMakeFiles/MServer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MServer.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sun/MServer/main.cpp -o CMakeFiles/MServer.dir/main.cpp.s

CMakeFiles/MServer.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/MServer.dir/main.cpp.o.requires

CMakeFiles/MServer.dir/main.cpp.o.provides: CMakeFiles/MServer.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/MServer.dir/build.make CMakeFiles/MServer.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/MServer.dir/main.cpp.o.provides

CMakeFiles/MServer.dir/main.cpp.o.provides.build: CMakeFiles/MServer.dir/main.cpp.o


# Object files for target MServer
MServer_OBJECTS = \
"CMakeFiles/MServer.dir/main.cpp.o"

# External object files for target MServer
MServer_EXTERNAL_OBJECTS =

MServer: CMakeFiles/MServer.dir/main.cpp.o
MServer: CMakeFiles/MServer.dir/build.make
MServer: CMakeFiles/MServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sun/MServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MServer.dir/build: MServer

.PHONY : CMakeFiles/MServer.dir/build

CMakeFiles/MServer.dir/requires: CMakeFiles/MServer.dir/main.cpp.o.requires

.PHONY : CMakeFiles/MServer.dir/requires

CMakeFiles/MServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MServer.dir/clean

CMakeFiles/MServer.dir/depend:
	cd /home/sun/MServer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sun/MServer /home/sun/MServer /home/sun/MServer/cmake-build-debug /home/sun/MServer/cmake-build-debug /home/sun/MServer/cmake-build-debug/CMakeFiles/MServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MServer.dir/depend

