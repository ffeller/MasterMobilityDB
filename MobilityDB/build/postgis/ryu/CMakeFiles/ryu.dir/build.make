# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/flaris/git/MobilityDB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/flaris/git/MobilityDB/build

# Include any dependencies generated for this target.
include postgis/ryu/CMakeFiles/ryu.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include postgis/ryu/CMakeFiles/ryu.dir/compiler_depend.make

# Include the progress variables for this target.
include postgis/ryu/CMakeFiles/ryu.dir/progress.make

# Include the compile flags for this target's objects.
include postgis/ryu/CMakeFiles/ryu.dir/flags.make

postgis/ryu/CMakeFiles/ryu.dir/d2s.c.o: postgis/ryu/CMakeFiles/ryu.dir/flags.make
postgis/ryu/CMakeFiles/ryu.dir/d2s.c.o: ../postgis/ryu/d2s.c
postgis/ryu/CMakeFiles/ryu.dir/d2s.c.o: postgis/ryu/CMakeFiles/ryu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flaris/git/MobilityDB/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object postgis/ryu/CMakeFiles/ryu.dir/d2s.c.o"
	cd /home/flaris/git/MobilityDB/build/postgis/ryu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT postgis/ryu/CMakeFiles/ryu.dir/d2s.c.o -MF CMakeFiles/ryu.dir/d2s.c.o.d -o CMakeFiles/ryu.dir/d2s.c.o -c /home/flaris/git/MobilityDB/postgis/ryu/d2s.c

postgis/ryu/CMakeFiles/ryu.dir/d2s.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ryu.dir/d2s.c.i"
	cd /home/flaris/git/MobilityDB/build/postgis/ryu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/flaris/git/MobilityDB/postgis/ryu/d2s.c > CMakeFiles/ryu.dir/d2s.c.i

postgis/ryu/CMakeFiles/ryu.dir/d2s.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ryu.dir/d2s.c.s"
	cd /home/flaris/git/MobilityDB/build/postgis/ryu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/flaris/git/MobilityDB/postgis/ryu/d2s.c -o CMakeFiles/ryu.dir/d2s.c.s

ryu: postgis/ryu/CMakeFiles/ryu.dir/d2s.c.o
ryu: postgis/ryu/CMakeFiles/ryu.dir/build.make
.PHONY : ryu

# Rule to build all files generated by this target.
postgis/ryu/CMakeFiles/ryu.dir/build: ryu
.PHONY : postgis/ryu/CMakeFiles/ryu.dir/build

postgis/ryu/CMakeFiles/ryu.dir/clean:
	cd /home/flaris/git/MobilityDB/build/postgis/ryu && $(CMAKE_COMMAND) -P CMakeFiles/ryu.dir/cmake_clean.cmake
.PHONY : postgis/ryu/CMakeFiles/ryu.dir/clean

postgis/ryu/CMakeFiles/ryu.dir/depend:
	cd /home/flaris/git/MobilityDB/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/flaris/git/MobilityDB /home/flaris/git/MobilityDB/postgis/ryu /home/flaris/git/MobilityDB/build /home/flaris/git/MobilityDB/build/postgis/ryu /home/flaris/git/MobilityDB/build/postgis/ryu/CMakeFiles/ryu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : postgis/ryu/CMakeFiles/ryu.dir/depend
