# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /part2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /part2

# Include any dependencies generated for this target.
include CMakeFiles/parallel_map_examples.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/parallel_map_examples.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/parallel_map_examples.dir/flags.make

CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o: CMakeFiles/parallel_map_examples.dir/flags.make
CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o: parallel_map_examples.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/part2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o -c /part2/parallel_map_examples.cpp

CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /part2/parallel_map_examples.cpp > CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.i

CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /part2/parallel_map_examples.cpp -o CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.s

CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o.requires:

.PHONY : CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o.requires

CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o.provides: CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o.requires
	$(MAKE) -f CMakeFiles/parallel_map_examples.dir/build.make CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o.provides.build
.PHONY : CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o.provides

CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o.provides.build: CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o


# Object files for target parallel_map_examples
parallel_map_examples_OBJECTS = \
"CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o"

# External object files for target parallel_map_examples
parallel_map_examples_EXTERNAL_OBJECTS =

parallel_map_examples: CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o
parallel_map_examples: CMakeFiles/parallel_map_examples.dir/build.make
parallel_map_examples: lib/libgtest.a
parallel_map_examples: CMakeFiles/parallel_map_examples.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/part2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable parallel_map_examples"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/parallel_map_examples.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/parallel_map_examples.dir/build: parallel_map_examples

.PHONY : CMakeFiles/parallel_map_examples.dir/build

CMakeFiles/parallel_map_examples.dir/requires: CMakeFiles/parallel_map_examples.dir/parallel_map_examples.cpp.o.requires

.PHONY : CMakeFiles/parallel_map_examples.dir/requires

CMakeFiles/parallel_map_examples.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/parallel_map_examples.dir/cmake_clean.cmake
.PHONY : CMakeFiles/parallel_map_examples.dir/clean

CMakeFiles/parallel_map_examples.dir/depend:
	cd /part2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /part2 /part2 /part2 /part2 /part2/CMakeFiles/parallel_map_examples.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/parallel_map_examples.dir/depend
