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
include tests/CMakeFiles/testdict.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/testdict.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/testdict.dir/flags.make

tests/CMakeFiles/testdict.dir/testdict.c.o: tests/CMakeFiles/testdict.dir/flags.make
tests/CMakeFiles/testdict.dir/testdict.c.o: ../tests/testdict.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/dev/freeDiameter/fDbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/testdict.dir/testdict.c.o"
	cd /root/dev/freeDiameter/fDbuild/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/testdict.dir/testdict.c.o   -c /root/dev/freeDiameter/tests/testdict.c

tests/CMakeFiles/testdict.dir/testdict.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testdict.dir/testdict.c.i"
	cd /root/dev/freeDiameter/fDbuild/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/dev/freeDiameter/tests/testdict.c > CMakeFiles/testdict.dir/testdict.c.i

tests/CMakeFiles/testdict.dir/testdict.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testdict.dir/testdict.c.s"
	cd /root/dev/freeDiameter/fDbuild/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/dev/freeDiameter/tests/testdict.c -o CMakeFiles/testdict.dir/testdict.c.s

tests/CMakeFiles/testdict.dir/testdict.c.o.requires:

.PHONY : tests/CMakeFiles/testdict.dir/testdict.c.o.requires

tests/CMakeFiles/testdict.dir/testdict.c.o.provides: tests/CMakeFiles/testdict.dir/testdict.c.o.requires
	$(MAKE) -f tests/CMakeFiles/testdict.dir/build.make tests/CMakeFiles/testdict.dir/testdict.c.o.provides.build
.PHONY : tests/CMakeFiles/testdict.dir/testdict.c.o.provides

tests/CMakeFiles/testdict.dir/testdict.c.o.provides.build: tests/CMakeFiles/testdict.dir/testdict.c.o


# Object files for target testdict
testdict_OBJECTS = \
"CMakeFiles/testdict.dir/testdict.c.o"

# External object files for target testdict
testdict_EXTERNAL_OBJECTS =

tests/testdict: tests/CMakeFiles/testdict.dir/testdict.c.o
tests/testdict: tests/CMakeFiles/testdict.dir/build.make
tests/testdict: libfdcore/libfdcore.so.1.2.0
tests/testdict: /usr/lib64/libgnutls.so
tests/testdict: /usr/lib64/libgcrypt.so
tests/testdict: libfdproto/libfdproto.so.1.2.0
tests/testdict: tests/CMakeFiles/testdict.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/dev/freeDiameter/fDbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable testdict"
	cd /root/dev/freeDiameter/fDbuild/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testdict.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/testdict.dir/build: tests/testdict

.PHONY : tests/CMakeFiles/testdict.dir/build

tests/CMakeFiles/testdict.dir/requires: tests/CMakeFiles/testdict.dir/testdict.c.o.requires

.PHONY : tests/CMakeFiles/testdict.dir/requires

tests/CMakeFiles/testdict.dir/clean:
	cd /root/dev/freeDiameter/fDbuild/tests && $(CMAKE_COMMAND) -P CMakeFiles/testdict.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/testdict.dir/clean

tests/CMakeFiles/testdict.dir/depend:
	cd /root/dev/freeDiameter/fDbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/dev/freeDiameter /root/dev/freeDiameter/tests /root/dev/freeDiameter/fDbuild /root/dev/freeDiameter/fDbuild/tests /root/dev/freeDiameter/fDbuild/tests/CMakeFiles/testdict.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/testdict.dir/depend

