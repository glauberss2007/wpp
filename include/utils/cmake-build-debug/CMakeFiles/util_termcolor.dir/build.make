# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/util_termcolor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/util_termcolor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/util_termcolor.dir/flags.make

CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o: CMakeFiles/util_termcolor.dir/flags.make
CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o: ../tools/streams/termcolor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o -c /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/tools/streams/termcolor.cpp

CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/tools/streams/termcolor.cpp > CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.i

CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/tools/streams/termcolor.cpp -o CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.s

CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o.requires:

.PHONY : CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o.requires

CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o.provides: CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o.requires
	$(MAKE) -f CMakeFiles/util_termcolor.dir/build.make CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o.provides.build
.PHONY : CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o.provides

CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o.provides.build: CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o


# Object files for target util_termcolor
util_termcolor_OBJECTS = \
"CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o"

# External object files for target util_termcolor
util_termcolor_EXTERNAL_OBJECTS =

util_termcolor: CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o
util_termcolor: CMakeFiles/util_termcolor.dir/build.make
util_termcolor: CMakeFiles/util_termcolor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable util_termcolor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/util_termcolor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/util_termcolor.dir/build: util_termcolor

.PHONY : CMakeFiles/util_termcolor.dir/build

CMakeFiles/util_termcolor.dir/requires: CMakeFiles/util_termcolor.dir/tools/streams/termcolor.cpp.o.requires

.PHONY : CMakeFiles/util_termcolor.dir/requires

CMakeFiles/util_termcolor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/util_termcolor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/util_termcolor.dir/clean

CMakeFiles/util_termcolor.dir/depend:
	cd /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug/CMakeFiles/util_termcolor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/util_termcolor.dir/depend

