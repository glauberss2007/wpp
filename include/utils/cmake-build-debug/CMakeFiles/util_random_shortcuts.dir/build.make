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
include CMakeFiles/util_random_shortcuts.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/util_random_shortcuts.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/util_random_shortcuts.dir/flags.make

CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o: CMakeFiles/util_random_shortcuts.dir/flags.make
CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o: ../tools/numeric/random_shortcuts.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o -c /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/tools/numeric/random_shortcuts.cpp

CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/tools/numeric/random_shortcuts.cpp > CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.i

CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/tools/numeric/random_shortcuts.cpp -o CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.s

CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o.requires:

.PHONY : CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o.requires

CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o.provides: CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o.requires
	$(MAKE) -f CMakeFiles/util_random_shortcuts.dir/build.make CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o.provides.build
.PHONY : CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o.provides

CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o.provides.build: CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o


# Object files for target util_random_shortcuts
util_random_shortcuts_OBJECTS = \
"CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o"

# External object files for target util_random_shortcuts
util_random_shortcuts_EXTERNAL_OBJECTS =

util_random_shortcuts: CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o
util_random_shortcuts: CMakeFiles/util_random_shortcuts.dir/build.make
util_random_shortcuts: CMakeFiles/util_random_shortcuts.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable util_random_shortcuts"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/util_random_shortcuts.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/util_random_shortcuts.dir/build: util_random_shortcuts

.PHONY : CMakeFiles/util_random_shortcuts.dir/build

CMakeFiles/util_random_shortcuts.dir/requires: CMakeFiles/util_random_shortcuts.dir/tools/numeric/random_shortcuts.cpp.o.requires

.PHONY : CMakeFiles/util_random_shortcuts.dir/requires

CMakeFiles/util_random_shortcuts.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/util_random_shortcuts.dir/cmake_clean.cmake
.PHONY : CMakeFiles/util_random_shortcuts.dir/clean

CMakeFiles/util_random_shortcuts.dir/depend:
	cd /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug/CMakeFiles/util_random_shortcuts.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/util_random_shortcuts.dir/depend

