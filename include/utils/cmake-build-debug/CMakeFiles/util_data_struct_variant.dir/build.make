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
include CMakeFiles/util_data_struct_variant.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/util_data_struct_variant.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/util_data_struct_variant.dir/flags.make

CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o: CMakeFiles/util_data_struct_variant.dir/flags.make
CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o: ../tools/data_structures/variant.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o -c /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/tools/data_structures/variant.cpp

CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/tools/data_structures/variant.cpp > CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.i

CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/tools/data_structures/variant.cpp -o CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.s

CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o.requires:

.PHONY : CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o.requires

CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o.provides: CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o.requires
	$(MAKE) -f CMakeFiles/util_data_struct_variant.dir/build.make CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o.provides.build
.PHONY : CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o.provides

CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o.provides.build: CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o


# Object files for target util_data_struct_variant
util_data_struct_variant_OBJECTS = \
"CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o"

# External object files for target util_data_struct_variant
util_data_struct_variant_EXTERNAL_OBJECTS =

util_data_struct_variant: CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o
util_data_struct_variant: CMakeFiles/util_data_struct_variant.dir/build.make
util_data_struct_variant: CMakeFiles/util_data_struct_variant.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable util_data_struct_variant"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/util_data_struct_variant.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/util_data_struct_variant.dir/build: util_data_struct_variant

.PHONY : CMakeFiles/util_data_struct_variant.dir/build

CMakeFiles/util_data_struct_variant.dir/requires: CMakeFiles/util_data_struct_variant.dir/tools/data_structures/variant.cpp.o.requires

.PHONY : CMakeFiles/util_data_struct_variant.dir/requires

CMakeFiles/util_data_struct_variant.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/util_data_struct_variant.dir/cmake_clean.cmake
.PHONY : CMakeFiles/util_data_struct_variant.dir/clean

CMakeFiles/util_data_struct_variant.dir/depend:
	cd /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug/CMakeFiles/util_data_struct_variant.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/util_data_struct_variant.dir/depend

