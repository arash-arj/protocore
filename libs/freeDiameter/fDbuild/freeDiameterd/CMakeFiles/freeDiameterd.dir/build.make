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
include freeDiameterd/CMakeFiles/freeDiameterd.dir/depend.make

# Include the progress variables for this target.
include freeDiameterd/CMakeFiles/freeDiameterd.dir/progress.make

# Include the compile flags for this target's objects.
include freeDiameterd/CMakeFiles/freeDiameterd.dir/flags.make

freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.o: freeDiameterd/CMakeFiles/freeDiameterd.dir/flags.make
freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.o: ../freeDiameterd/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/dev/freeDiameter/fDbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.o"
	cd /root/dev/freeDiameter/fDbuild/freeDiameterd && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/freeDiameterd.dir/main.c.o   -c /root/dev/freeDiameter/freeDiameterd/main.c

freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freeDiameterd.dir/main.c.i"
	cd /root/dev/freeDiameter/fDbuild/freeDiameterd && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/dev/freeDiameter/freeDiameterd/main.c > CMakeFiles/freeDiameterd.dir/main.c.i

freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freeDiameterd.dir/main.c.s"
	cd /root/dev/freeDiameter/fDbuild/freeDiameterd && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/dev/freeDiameter/freeDiameterd/main.c -o CMakeFiles/freeDiameterd.dir/main.c.s

freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.o.requires:

.PHONY : freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.o.requires

freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.o.provides: freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.o.requires
	$(MAKE) -f freeDiameterd/CMakeFiles/freeDiameterd.dir/build.make freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.o.provides.build
.PHONY : freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.o.provides

freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.o.provides.build: freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.o


# Object files for target freeDiameterd
freeDiameterd_OBJECTS = \
"CMakeFiles/freeDiameterd.dir/main.c.o"

# External object files for target freeDiameterd
freeDiameterd_EXTERNAL_OBJECTS =

freeDiameterd/freeDiameterd-1.2.0: freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.o
freeDiameterd/freeDiameterd-1.2.0: freeDiameterd/CMakeFiles/freeDiameterd.dir/build.make
freeDiameterd/freeDiameterd-1.2.0: libfdcore/libfdcore.so.1.2.0
freeDiameterd/freeDiameterd-1.2.0: /usr/lib64/libgnutls.so
freeDiameterd/freeDiameterd-1.2.0: libfdproto/libfdproto.so.1.2.0
freeDiameterd/freeDiameterd-1.2.0: freeDiameterd/CMakeFiles/freeDiameterd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/dev/freeDiameter/fDbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable freeDiameterd"
	cd /root/dev/freeDiameter/fDbuild/freeDiameterd && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freeDiameterd.dir/link.txt --verbose=$(VERBOSE)
	cd /root/dev/freeDiameter/fDbuild/freeDiameterd && $(CMAKE_COMMAND) -E cmake_symlink_executable freeDiameterd-1.2.0 freeDiameterd

freeDiameterd/freeDiameterd: freeDiameterd/freeDiameterd-1.2.0


# Rule to build all files generated by this target.
freeDiameterd/CMakeFiles/freeDiameterd.dir/build: freeDiameterd/freeDiameterd

.PHONY : freeDiameterd/CMakeFiles/freeDiameterd.dir/build

freeDiameterd/CMakeFiles/freeDiameterd.dir/requires: freeDiameterd/CMakeFiles/freeDiameterd.dir/main.c.o.requires

.PHONY : freeDiameterd/CMakeFiles/freeDiameterd.dir/requires

freeDiameterd/CMakeFiles/freeDiameterd.dir/clean:
	cd /root/dev/freeDiameter/fDbuild/freeDiameterd && $(CMAKE_COMMAND) -P CMakeFiles/freeDiameterd.dir/cmake_clean.cmake
.PHONY : freeDiameterd/CMakeFiles/freeDiameterd.dir/clean

freeDiameterd/CMakeFiles/freeDiameterd.dir/depend:
	cd /root/dev/freeDiameter/fDbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/dev/freeDiameter /root/dev/freeDiameter/freeDiameterd /root/dev/freeDiameter/fDbuild /root/dev/freeDiameter/fDbuild/freeDiameterd /root/dev/freeDiameter/fDbuild/freeDiameterd/CMakeFiles/freeDiameterd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : freeDiameterd/CMakeFiles/freeDiameterd.dir/depend
