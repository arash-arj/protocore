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
include tests/CMakeFiles/testpeers.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/testpeers.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/testpeers.dir/flags.make

tests/CMakeFiles/testpeers.dir/testpeers.c.o: tests/CMakeFiles/testpeers.dir/flags.make
tests/CMakeFiles/testpeers.dir/testpeers.c.o: ../tests/testpeers.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/dev/freeDiameter/fDbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/testpeers.dir/testpeers.c.o"
	cd /root/dev/freeDiameter/fDbuild/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/testpeers.dir/testpeers.c.o   -c /root/dev/freeDiameter/tests/testpeers.c

tests/CMakeFiles/testpeers.dir/testpeers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testpeers.dir/testpeers.c.i"
	cd /root/dev/freeDiameter/fDbuild/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/dev/freeDiameter/tests/testpeers.c > CMakeFiles/testpeers.dir/testpeers.c.i

tests/CMakeFiles/testpeers.dir/testpeers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testpeers.dir/testpeers.c.s"
	cd /root/dev/freeDiameter/fDbuild/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/dev/freeDiameter/tests/testpeers.c -o CMakeFiles/testpeers.dir/testpeers.c.s

tests/CMakeFiles/testpeers.dir/testpeers.c.o.requires:

.PHONY : tests/CMakeFiles/testpeers.dir/testpeers.c.o.requires

tests/CMakeFiles/testpeers.dir/testpeers.c.o.provides: tests/CMakeFiles/testpeers.dir/testpeers.c.o.requires
	$(MAKE) -f tests/CMakeFiles/testpeers.dir/build.make tests/CMakeFiles/testpeers.dir/testpeers.c.o.provides.build
.PHONY : tests/CMakeFiles/testpeers.dir/testpeers.c.o.provides

tests/CMakeFiles/testpeers.dir/testpeers.c.o.provides.build: tests/CMakeFiles/testpeers.dir/testpeers.c.o


# Object files for target testpeers
testpeers_OBJECTS = \
"CMakeFiles/testpeers.dir/testpeers.c.o"

# External object files for target testpeers
testpeers_EXTERNAL_OBJECTS =

tests/testpeers: tests/CMakeFiles/testpeers.dir/testpeers.c.o
tests/testpeers: tests/CMakeFiles/testpeers.dir/build.make
tests/testpeers: libfdcore/libfdcore.so.1.2.0
tests/testpeers: /usr/lib64/libgnutls.so
tests/testpeers: /usr/lib64/libgcrypt.so
tests/testpeers: libfdproto/libfdproto.so.1.2.0
tests/testpeers: tests/CMakeFiles/testpeers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/dev/freeDiameter/fDbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable testpeers"
	cd /root/dev/freeDiameter/fDbuild/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testpeers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/testpeers.dir/build: tests/testpeers

.PHONY : tests/CMakeFiles/testpeers.dir/build

tests/CMakeFiles/testpeers.dir/requires: tests/CMakeFiles/testpeers.dir/testpeers.c.o.requires

.PHONY : tests/CMakeFiles/testpeers.dir/requires

tests/CMakeFiles/testpeers.dir/clean:
	cd /root/dev/freeDiameter/fDbuild/tests && $(CMAKE_COMMAND) -P CMakeFiles/testpeers.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/testpeers.dir/clean

tests/CMakeFiles/testpeers.dir/depend:
	cd /root/dev/freeDiameter/fDbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/dev/freeDiameter /root/dev/freeDiameter/tests /root/dev/freeDiameter/fDbuild /root/dev/freeDiameter/fDbuild/tests /root/dev/freeDiameter/fDbuild/tests/CMakeFiles/testpeers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/testpeers.dir/depend

