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
include extensions/dbg_rt/CMakeFiles/dbg_rt.dir/depend.make

# Include the progress variables for this target.
include extensions/dbg_rt/CMakeFiles/dbg_rt.dir/progress.make

# Include the compile flags for this target's objects.
include extensions/dbg_rt/CMakeFiles/dbg_rt.dir/flags.make

extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.o: extensions/dbg_rt/CMakeFiles/dbg_rt.dir/flags.make
extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.o: ../extensions/dbg_rt/dbg_rt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/dev/freeDiameter/fDbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.o"
	cd /root/dev/freeDiameter/fDbuild/extensions/dbg_rt && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dbg_rt.dir/dbg_rt.c.o   -c /root/dev/freeDiameter/extensions/dbg_rt/dbg_rt.c

extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dbg_rt.dir/dbg_rt.c.i"
	cd /root/dev/freeDiameter/fDbuild/extensions/dbg_rt && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/dev/freeDiameter/extensions/dbg_rt/dbg_rt.c > CMakeFiles/dbg_rt.dir/dbg_rt.c.i

extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dbg_rt.dir/dbg_rt.c.s"
	cd /root/dev/freeDiameter/fDbuild/extensions/dbg_rt && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/dev/freeDiameter/extensions/dbg_rt/dbg_rt.c -o CMakeFiles/dbg_rt.dir/dbg_rt.c.s

extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.o.requires:

.PHONY : extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.o.requires

extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.o.provides: extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.o.requires
	$(MAKE) -f extensions/dbg_rt/CMakeFiles/dbg_rt.dir/build.make extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.o.provides.build
.PHONY : extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.o.provides

extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.o.provides.build: extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.o


# Object files for target dbg_rt
dbg_rt_OBJECTS = \
"CMakeFiles/dbg_rt.dir/dbg_rt.c.o"

# External object files for target dbg_rt
dbg_rt_EXTERNAL_OBJECTS =

extensions/dbg_rt.fdx: extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.o
extensions/dbg_rt.fdx: extensions/dbg_rt/CMakeFiles/dbg_rt.dir/build.make
extensions/dbg_rt.fdx: extensions/dbg_rt/CMakeFiles/dbg_rt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/dev/freeDiameter/fDbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared module ../dbg_rt.fdx"
	cd /root/dev/freeDiameter/fDbuild/extensions/dbg_rt && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dbg_rt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extensions/dbg_rt/CMakeFiles/dbg_rt.dir/build: extensions/dbg_rt.fdx

.PHONY : extensions/dbg_rt/CMakeFiles/dbg_rt.dir/build

extensions/dbg_rt/CMakeFiles/dbg_rt.dir/requires: extensions/dbg_rt/CMakeFiles/dbg_rt.dir/dbg_rt.c.o.requires

.PHONY : extensions/dbg_rt/CMakeFiles/dbg_rt.dir/requires

extensions/dbg_rt/CMakeFiles/dbg_rt.dir/clean:
	cd /root/dev/freeDiameter/fDbuild/extensions/dbg_rt && $(CMAKE_COMMAND) -P CMakeFiles/dbg_rt.dir/cmake_clean.cmake
.PHONY : extensions/dbg_rt/CMakeFiles/dbg_rt.dir/clean

extensions/dbg_rt/CMakeFiles/dbg_rt.dir/depend:
	cd /root/dev/freeDiameter/fDbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/dev/freeDiameter /root/dev/freeDiameter/extensions/dbg_rt /root/dev/freeDiameter/fDbuild /root/dev/freeDiameter/fDbuild/extensions/dbg_rt /root/dev/freeDiameter/fDbuild/extensions/dbg_rt/CMakeFiles/dbg_rt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extensions/dbg_rt/CMakeFiles/dbg_rt.dir/depend

