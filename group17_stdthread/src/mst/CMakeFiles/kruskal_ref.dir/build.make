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
include src/mst/CMakeFiles/kruskal_ref.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/mst/CMakeFiles/kruskal_ref.dir/compiler_depend.make

# Include the progress variables for this target.
include src/mst/CMakeFiles/kruskal_ref.dir/progress.make

# Include the compile flags for this target's objects.
include src/mst/CMakeFiles/kruskal_ref.dir/flags.make

src/mst/CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.o: src/mst/CMakeFiles/kruskal_ref.dir/flags.make
src/mst/CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.o: src/mst/kruskal_ref.cpp
src/mst/CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.o: src/mst/CMakeFiles/kruskal_ref.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/d/group17_stdthread/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/mst/CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.o"
	cd /cygdrive/d/group17_stdthread/src/mst && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/mst/CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.o -MF CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.o.d -o CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.o -c /cygdrive/d/group17_stdthread/src/mst/kruskal_ref.cpp

src/mst/CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.i"
	cd /cygdrive/d/group17_stdthread/src/mst && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/d/group17_stdthread/src/mst/kruskal_ref.cpp > CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.i

src/mst/CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.s"
	cd /cygdrive/d/group17_stdthread/src/mst && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/d/group17_stdthread/src/mst/kruskal_ref.cpp -o CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.s

# Object files for target kruskal_ref
kruskal_ref_OBJECTS = \
"CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.o"

# External object files for target kruskal_ref
kruskal_ref_EXTERNAL_OBJECTS =

bin/kruskal_ref.exe: src/mst/CMakeFiles/kruskal_ref.dir/kruskal_ref.cpp.o
bin/kruskal_ref.exe: src/mst/CMakeFiles/kruskal_ref.dir/build.make
bin/kruskal_ref.exe: src/utils/libgraph.a
bin/kruskal_ref.exe: src/mst/CMakeFiles/kruskal_ref.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/d/group17_stdthread/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/kruskal_ref.exe"
	cd /cygdrive/d/group17_stdthread/src/mst && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kruskal_ref.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/mst/CMakeFiles/kruskal_ref.dir/build: bin/kruskal_ref.exe
.PHONY : src/mst/CMakeFiles/kruskal_ref.dir/build

src/mst/CMakeFiles/kruskal_ref.dir/clean:
	cd /cygdrive/d/group17_stdthread/src/mst && $(CMAKE_COMMAND) -P CMakeFiles/kruskal_ref.dir/cmake_clean.cmake
.PHONY : src/mst/CMakeFiles/kruskal_ref.dir/clean

src/mst/CMakeFiles/kruskal_ref.dir/depend:
	cd /cygdrive/d/group17_stdthread && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/d/group17_stdthread /cygdrive/d/group17_stdthread/src/mst /cygdrive/d/group17_stdthread /cygdrive/d/group17_stdthread/src/mst /cygdrive/d/group17_stdthread/src/mst/CMakeFiles/kruskal_ref.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/mst/CMakeFiles/kruskal_ref.dir/depend

