# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /root/dev/freeDiameter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/dev/freeDiameter/fDbuild

# Include any dependencies generated for this target.
include extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/depend.make

# Include the progress variables for this target.
include extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/progress.make

# Include the compile flags for this target's objects.
include extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/flags.make

extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o: extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/flags.make
extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o: ../extensions/rt_change_dh/rt_change_dh.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/dev/freeDiameter/fDbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o"
	cd /root/dev/freeDiameter/fDbuild/extensions/rt_change_dh && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o   -c /root/dev/freeDiameter/extensions/rt_change_dh/rt_change_dh.c

extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rt_change_dh.dir/rt_change_dh.c.i"
	cd /root/dev/freeDiameter/fDbuild/extensions/rt_change_dh && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/dev/freeDiameter/extensions/rt_change_dh/rt_change_dh.c > CMakeFiles/rt_change_dh.dir/rt_change_dh.c.i

extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rt_change_dh.dir/rt_change_dh.c.s"
	cd /root/dev/freeDiameter/fDbuild/extensions/rt_change_dh && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/dev/freeDiameter/extensions/rt_change_dh/rt_change_dh.c -o CMakeFiles/rt_change_dh.dir/rt_change_dh.c.s

extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o.requires:

.PHONY : extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o.requires

extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o.provides: extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o.requires
	$(MAKE) -f extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/build.make extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o.provides.build
.PHONY : extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o.provides

extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o.provides.build: extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o


# Object files for target rt_change_dh
rt_change_dh_OBJECTS = \
"CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o"

# External object files for target rt_change_dh
rt_change_dh_EXTERNAL_OBJECTS =

extensions/rt_change_dh.fdx: extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o
extensions/rt_change_dh.fdx: extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/build.make
extensions/rt_change_dh.fdx: extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/dev/freeDiameter/fDbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared module ../rt_change_dh.fdx"
	cd /root/dev/freeDiameter/fDbuild/extensions/rt_change_dh && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rt_change_dh.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/build: extensions/rt_change_dh.fdx

.PHONY : extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/build

extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/requires: extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/rt_change_dh.c.o.requires

.PHONY : extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/requires

extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/clean:
	cd /root/dev/freeDiameter/fDbuild/extensions/rt_change_dh && $(CMAKE_COMMAND) -P CMakeFiles/rt_change_dh.dir/cmake_clean.cmake
.PHONY : extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/clean

extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/depend:
	cd /root/dev/freeDiameter/fDbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/dev/freeDiameter /root/dev/freeDiameter/extensions/rt_change_dh /root/dev/freeDiameter/fDbuild /root/dev/freeDiameter/fDbuild/extensions/rt_change_dh /root/dev/freeDiameter/fDbuild/extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extensions/rt_change_dh/CMakeFiles/rt_change_dh.dir/depend

