# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/d/group17_stdthread

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/d/group17_stdthread

# Include any dependencies generated for this target.
include src/utils/CMakeFiles/graph.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/utils/CMakeFiles/graph.dir/compiler_depend.make

# Include the progress variables for this target.
include src/utils/CMakeFiles/graph.dir/progress.make

# Include the compile flags for this target's objects.
include src/utils/CMakeFiles/graph.dir/flags.make

src/utils/CMakeFiles/graph.dir/graph.cpp.o: src/utils/CMakeFiles/graph.dir/flags.make
src/utils/CMakeFiles/graph.dir/graph.cpp.o: src/utils/graph.cpp
src/utils/CMakeFiles/graph.dir/graph.cpp.o: src/utils/CMakeFiles/graph.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/d/group17_stdthread/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/utils/CMakeFiles/graph.dir/graph.cpp.o"
	cd /cygdrive/d/group17_stdthread/src/utils && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/utils/CMakeFiles/graph.dir/graph.cpp.o -MF CMakeFiles/graph.dir/graph.cpp.o.d -o CMakeFiles/graph.dir/graph.cpp.o -c /cygdrive/d/group17_stdthread/src/utils/graph.cpp

src/utils/CMakeFiles/graph.dir/graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graph.dir/graph.cpp.i"
	cd /cygdrive/d/group17_stdthread/src/utils && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/d/group17_stdthread/src/utils/graph.cpp > CMakeFiles/graph.dir/graph.cpp.i

src/utils/CMakeFiles/graph.dir/graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graph.dir/graph.cpp.s"
	cd /cygdrive/d/group17_stdthread/src/utils && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/d/group17_stdthread/src/utils/graph.cpp -o CMakeFiles/graph.dir/graph.cpp.s

src/utils/CMakeFiles/graph.dir/disjoint_set.cpp.o: src/utils/CMakeFiles/graph.dir/flags.make
src/utils/CMakeFiles/graph.dir/disjoint_set.cpp.o: src/utils/disjoint_set.cpp
src/utils/CMakeFiles/graph.dir/disjoint_set.cpp.o: src/utils/CMakeFiles/graph.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/d/group17_stdthread/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/utils/CMakeFiles/graph.dir/disjoint_set.cpp.o"
	cd /cygdrive/d/group17_stdthread/src/utils && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/utils/CMakeFiles/graph.dir/disjoint_set.cpp.o -MF CMakeFiles/graph.dir/disjoint_set.cpp.o.d -o CMakeFiles/graph.dir/disjoint_set.cpp.o -c /cygdrive/d/group17_stdthread/src/utils/disjoint_set.cpp

src/utils/CMakeFiles/graph.dir/disjoint_set.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graph.dir/disjoint_set.cpp.i"
	cd /cygdrive/d/group17_stdthread/src/utils && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/d/group17_stdthread/src/utils/disjoint_set.cpp > CMakeFiles/graph.dir/disjoint_set.cpp.i

src/utils/CMakeFiles/graph.dir/disjoint_set.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graph.dir/disjoint_set.cpp.s"
	cd /cygdrive/d/group17_stdthread/src/utils && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/d/group17_stdthread/src/utils/disjoint_set.cpp -o CMakeFiles/graph.dir/disjoint_set.cpp.s

# Object files for target graph
graph_OBJECTS = \
"CMakeFiles/graph.dir/graph.cpp.o" \
"CMakeFiles/graph.dir/disjoint_set.cpp.o"

# External object files for target graph
graph_EXTERNAL_OBJECTS =

src/utils/libgraph.a: src/utils/CMakeFiles/graph.dir/graph.cpp.o
src/utils/libgraph.a: src/utils/CMakeFiles/graph.dir/disjoint_set.cpp.o
src/utils/libgraph.a: src/utils/CMakeFiles/graph.dir/build.make
src/utils/libgraph.a: src/utils/CMakeFiles/graph.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/d/group17_stdthread/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libgraph.a"
	cd /cygdrive/d/group17_stdthread/src/utils && $(CMAKE_COMMAND) -P CMakeFiles/graph.dir/cmake_clean_target.cmake
	cd /cygdrive/d/group17_stdthread/src/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graph.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/utils/CMakeFiles/graph.dir/build: src/utils/libgraph.a
.PHONY : src/utils/CMakeFiles/graph.dir/build

src/utils/CMakeFiles/graph.dir/clean:
	cd /cygdrive/d/group17_stdthread/src/utils && $(CMAKE_COMMAND) -P CMakeFiles/graph.dir/cmake_clean.cmake
.PHONY : src/utils/CMakeFiles/graph.dir/clean

src/utils/CMakeFiles/graph.dir/depend:
	cd /cygdrive/d/group17_stdthread && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/d/group17_stdthread /cygdrive/d/group17_stdthread/src/utils /cygdrive/d/group17_stdthread /cygdrive/d/group17_stdthread/src/utils /cygdrive/d/group17_stdthread/src/utils/CMakeFiles/graph.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/utils/CMakeFiles/graph.dir/depend

