# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/toodles/madness/analysis/External/Mt2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/toodles/madness/analysis/build/Mt2

# Include any dependencies generated for this target.
include CMakeFiles/Mt2Example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Mt2Example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Mt2Example.dir/flags.make

CMakeFiles/Mt2Example.dir/example.cpp.o: CMakeFiles/Mt2Example.dir/flags.make
CMakeFiles/Mt2Example.dir/example.cpp.o: /home/toodles/madness/analysis/External/Mt2/example.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/toodles/madness/analysis/build/Mt2/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Mt2Example.dir/example.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Mt2Example.dir/example.cpp.o -c /home/toodles/madness/analysis/External/Mt2/example.cpp

CMakeFiles/Mt2Example.dir/example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Mt2Example.dir/example.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/toodles/madness/analysis/External/Mt2/example.cpp > CMakeFiles/Mt2Example.dir/example.cpp.i

CMakeFiles/Mt2Example.dir/example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Mt2Example.dir/example.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/toodles/madness/analysis/External/Mt2/example.cpp -o CMakeFiles/Mt2Example.dir/example.cpp.s

CMakeFiles/Mt2Example.dir/example.cpp.o.requires:
.PHONY : CMakeFiles/Mt2Example.dir/example.cpp.o.requires

CMakeFiles/Mt2Example.dir/example.cpp.o.provides: CMakeFiles/Mt2Example.dir/example.cpp.o.requires
	$(MAKE) -f CMakeFiles/Mt2Example.dir/build.make CMakeFiles/Mt2Example.dir/example.cpp.o.provides.build
.PHONY : CMakeFiles/Mt2Example.dir/example.cpp.o.provides

CMakeFiles/Mt2Example.dir/example.cpp.o.provides.build: CMakeFiles/Mt2Example.dir/example.cpp.o

# Object files for target Mt2Example
Mt2Example_OBJECTS = \
"CMakeFiles/Mt2Example.dir/example.cpp.o"

# External object files for target Mt2Example
Mt2Example_EXTERNAL_OBJECTS =

bin/Mt2Example: CMakeFiles/Mt2Example.dir/example.cpp.o
bin/Mt2Example: CMakeFiles/Mt2Example.dir/build.make
bin/Mt2Example: lib/libMt2.so.0.1.0
bin/Mt2Example: CMakeFiles/Mt2Example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/Mt2Example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Mt2Example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Mt2Example.dir/build: bin/Mt2Example
.PHONY : CMakeFiles/Mt2Example.dir/build

CMakeFiles/Mt2Example.dir/requires: CMakeFiles/Mt2Example.dir/example.cpp.o.requires
.PHONY : CMakeFiles/Mt2Example.dir/requires

CMakeFiles/Mt2Example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Mt2Example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Mt2Example.dir/clean

CMakeFiles/Mt2Example.dir/depend:
	cd /home/toodles/madness/analysis/build/Mt2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/toodles/madness/analysis/External/Mt2 /home/toodles/madness/analysis/External/Mt2 /home/toodles/madness/analysis/build/Mt2 /home/toodles/madness/analysis/build/Mt2 /home/toodles/madness/analysis/build/Mt2/CMakeFiles/Mt2Example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Mt2Example.dir/depend
