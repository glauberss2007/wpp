# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /snap/clion/52/bin/cmake/bin/cmake

# The command to remove a file.
RM = /snap/clion/52/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/glauber/CLionProjects/wppcopy2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/glauber/CLionProjects/wppcopy2/cmake-build-debug

# Include any dependencies generated for this target.
include tools/tests/benchmarks/CMakeFiles/benchmarks.dir/depend.make

# Include the progress variables for this target.
include tools/tests/benchmarks/CMakeFiles/benchmarks.dir/progress.make

# Include the compile flags for this target's objects.
include tools/tests/benchmarks/CMakeFiles/benchmarks.dir/flags.make

tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.o: tools/tests/benchmarks/CMakeFiles/benchmarks.dir/flags.make
tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.o: ../tools/tests/benchmarks/benchmarks.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppcopy2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.o"
	cd /home/glauber/CLionProjects/wppcopy2/cmake-build-debug/tools/tests/benchmarks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmarks.dir/benchmarks.cpp.o -c /home/glauber/CLionProjects/wppcopy2/tools/tests/benchmarks/benchmarks.cpp

tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmarks.dir/benchmarks.cpp.i"
	cd /home/glauber/CLionProjects/wppcopy2/cmake-build-debug/tools/tests/benchmarks && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppcopy2/tools/tests/benchmarks/benchmarks.cpp > CMakeFiles/benchmarks.dir/benchmarks.cpp.i

tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmarks.dir/benchmarks.cpp.s"
	cd /home/glauber/CLionProjects/wppcopy2/cmake-build-debug/tools/tests/benchmarks && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppcopy2/tools/tests/benchmarks/benchmarks.cpp -o CMakeFiles/benchmarks.dir/benchmarks.cpp.s

tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.o.requires:

.PHONY : tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.o.requires

tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.o.provides: tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.o.requires
	$(MAKE) -f tools/tests/benchmarks/CMakeFiles/benchmarks.dir/build.make tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.o.provides.build
.PHONY : tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.o.provides

tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.o.provides.build: tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.o


# Object files for target benchmarks
benchmarks_OBJECTS = \
"CMakeFiles/benchmarks.dir/benchmarks.cpp.o"

# External object files for target benchmarks
benchmarks_EXTERNAL_OBJECTS =

tools/tests/benchmarks/benchmarks: tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.o
tools/tests/benchmarks/benchmarks: tools/tests/benchmarks/CMakeFiles/benchmarks.dir/build.make
tools/tests/benchmarks/benchmarks: /usr/lib/x86_64-linux-gnu/libssl.so
tools/tests/benchmarks/benchmarks: /usr/lib/x86_64-linux-gnu/libcrypto.so
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_filesystem.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_regex.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_system.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_iostreams.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_date_time.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_chrono.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_timer.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_thread.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_coroutine.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_log.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_program_options.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_serialization.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_atomic.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_context.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_log_setup.a
tools/tests/benchmarks/benchmarks: components/libua-parser.a
tools/tests/benchmarks/benchmarks: components/google_benchmark/src/libbenchmark.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_filesystem.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_regex.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_system.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_iostreams.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_date_time.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_chrono.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_timer.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_thread.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_coroutine.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_log.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_program_options.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_serialization.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_atomic.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_context.a
tools/tests/benchmarks/benchmarks: /usr/local/lib/libboost_log_setup.a
tools/tests/benchmarks/benchmarks: components/yaml-cpp/libyaml-cpp.a
tools/tests/benchmarks/benchmarks: /usr/lib/x86_64-linux-gnu/librt.so
tools/tests/benchmarks/benchmarks: tools/tests/benchmarks/CMakeFiles/benchmarks.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/glauber/CLionProjects/wppcopy2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable benchmarks"
	cd /home/glauber/CLionProjects/wppcopy2/cmake-build-debug/tools/tests/benchmarks && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/benchmarks.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/tests/benchmarks/CMakeFiles/benchmarks.dir/build: tools/tests/benchmarks/benchmarks

.PHONY : tools/tests/benchmarks/CMakeFiles/benchmarks.dir/build

tools/tests/benchmarks/CMakeFiles/benchmarks.dir/requires: tools/tests/benchmarks/CMakeFiles/benchmarks.dir/benchmarks.cpp.o.requires

.PHONY : tools/tests/benchmarks/CMakeFiles/benchmarks.dir/requires

tools/tests/benchmarks/CMakeFiles/benchmarks.dir/clean:
	cd /home/glauber/CLionProjects/wppcopy2/cmake-build-debug/tools/tests/benchmarks && $(CMAKE_COMMAND) -P CMakeFiles/benchmarks.dir/cmake_clean.cmake
.PHONY : tools/tests/benchmarks/CMakeFiles/benchmarks.dir/clean

tools/tests/benchmarks/CMakeFiles/benchmarks.dir/depend:
	cd /home/glauber/CLionProjects/wppcopy2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/glauber/CLionProjects/wppcopy2 /home/glauber/CLionProjects/wppcopy2/tools/tests/benchmarks /home/glauber/CLionProjects/wppcopy2/cmake-build-debug /home/glauber/CLionProjects/wppcopy2/cmake-build-debug/tools/tests/benchmarks /home/glauber/CLionProjects/wppcopy2/cmake-build-debug/tools/tests/benchmarks/CMakeFiles/benchmarks.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/tests/benchmarks/CMakeFiles/benchmarks.dir/depend

