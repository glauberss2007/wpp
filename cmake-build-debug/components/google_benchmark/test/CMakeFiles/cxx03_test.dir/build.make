# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /snap/clion/81/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/81/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/glauber/CLionProjects/wppGitHub

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/glauber/CLionProjects/wppGitHub/cmake-build-debug

# Include any dependencies generated for this target.
include components/google_benchmark/test/CMakeFiles/cxx03_test.dir/depend.make

# Include the progress variables for this target.
include components/google_benchmark/test/CMakeFiles/cxx03_test.dir/progress.make

# Include the compile flags for this target's objects.
include components/google_benchmark/test/CMakeFiles/cxx03_test.dir/flags.make

components/google_benchmark/test/CMakeFiles/cxx03_test.dir/cxx03_test.cc.o: components/google_benchmark/test/CMakeFiles/cxx03_test.dir/flags.make
components/google_benchmark/test/CMakeFiles/cxx03_test.dir/cxx03_test.cc.o: ../components/google_benchmark/test/cxx03_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object components/google_benchmark/test/CMakeFiles/cxx03_test.dir/cxx03_test.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cxx03_test.dir/cxx03_test.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/test/cxx03_test.cc

components/google_benchmark/test/CMakeFiles/cxx03_test.dir/cxx03_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cxx03_test.dir/cxx03_test.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/test/cxx03_test.cc > CMakeFiles/cxx03_test.dir/cxx03_test.cc.i

components/google_benchmark/test/CMakeFiles/cxx03_test.dir/cxx03_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cxx03_test.dir/cxx03_test.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/test/cxx03_test.cc -o CMakeFiles/cxx03_test.dir/cxx03_test.cc.s

# Object files for target cxx03_test
cxx03_test_OBJECTS = \
"CMakeFiles/cxx03_test.dir/cxx03_test.cc.o"

# External object files for target cxx03_test
cxx03_test_EXTERNAL_OBJECTS =

components/google_benchmark/test/cxx03_test: components/google_benchmark/test/CMakeFiles/cxx03_test.dir/cxx03_test.cc.o
components/google_benchmark/test/cxx03_test: components/google_benchmark/test/CMakeFiles/cxx03_test.dir/build.make
components/google_benchmark/test/cxx03_test: components/google_benchmark/src/libbenchmark.a
components/google_benchmark/test/cxx03_test: /usr/lib/x86_64-linux-gnu/librt.so
components/google_benchmark/test/cxx03_test: components/google_benchmark/test/CMakeFiles/cxx03_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cxx03_test"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cxx03_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
components/google_benchmark/test/CMakeFiles/cxx03_test.dir/build: components/google_benchmark/test/cxx03_test

.PHONY : components/google_benchmark/test/CMakeFiles/cxx03_test.dir/build

components/google_benchmark/test/CMakeFiles/cxx03_test.dir/clean:
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/test && $(CMAKE_COMMAND) -P CMakeFiles/cxx03_test.dir/cmake_clean.cmake
.PHONY : components/google_benchmark/test/CMakeFiles/cxx03_test.dir/clean

components/google_benchmark/test/CMakeFiles/cxx03_test.dir/depend:
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/glauber/CLionProjects/wppGitHub /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/test /home/glauber/CLionProjects/wppGitHub/cmake-build-debug /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/test /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/test/CMakeFiles/cxx03_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : components/google_benchmark/test/CMakeFiles/cxx03_test.dir/depend

