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
include components/google_benchmark/src/CMakeFiles/benchmark.dir/depend.make

# Include the progress variables for this target.
include components/google_benchmark/src/CMakeFiles/benchmark.dir/progress.make

# Include the compile flags for this target's objects.
include components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make

components/google_benchmark/src/CMakeFiles/benchmark.dir/benchmark.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/benchmark.cc.o: ../components/google_benchmark/src/benchmark.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/benchmark.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/benchmark.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/benchmark.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/benchmark.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/benchmark.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/benchmark.cc > CMakeFiles/benchmark.dir/benchmark.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/benchmark.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/benchmark.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/benchmark.cc -o CMakeFiles/benchmark.dir/benchmark.cc.s

components/google_benchmark/src/CMakeFiles/benchmark.dir/benchmark_register.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/benchmark_register.cc.o: ../components/google_benchmark/src/benchmark_register.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/benchmark_register.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/benchmark_register.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/benchmark_register.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/benchmark_register.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/benchmark_register.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/benchmark_register.cc > CMakeFiles/benchmark.dir/benchmark_register.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/benchmark_register.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/benchmark_register.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/benchmark_register.cc -o CMakeFiles/benchmark.dir/benchmark_register.cc.s

components/google_benchmark/src/CMakeFiles/benchmark.dir/colorprint.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/colorprint.cc.o: ../components/google_benchmark/src/colorprint.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/colorprint.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/colorprint.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/colorprint.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/colorprint.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/colorprint.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/colorprint.cc > CMakeFiles/benchmark.dir/colorprint.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/colorprint.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/colorprint.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/colorprint.cc -o CMakeFiles/benchmark.dir/colorprint.cc.s

components/google_benchmark/src/CMakeFiles/benchmark.dir/commandlineflags.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/commandlineflags.cc.o: ../components/google_benchmark/src/commandlineflags.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/commandlineflags.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/commandlineflags.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/commandlineflags.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/commandlineflags.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/commandlineflags.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/commandlineflags.cc > CMakeFiles/benchmark.dir/commandlineflags.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/commandlineflags.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/commandlineflags.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/commandlineflags.cc -o CMakeFiles/benchmark.dir/commandlineflags.cc.s

components/google_benchmark/src/CMakeFiles/benchmark.dir/complexity.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/complexity.cc.o: ../components/google_benchmark/src/complexity.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/complexity.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/complexity.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/complexity.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/complexity.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/complexity.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/complexity.cc > CMakeFiles/benchmark.dir/complexity.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/complexity.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/complexity.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/complexity.cc -o CMakeFiles/benchmark.dir/complexity.cc.s

components/google_benchmark/src/CMakeFiles/benchmark.dir/console_reporter.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/console_reporter.cc.o: ../components/google_benchmark/src/console_reporter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/console_reporter.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/console_reporter.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/console_reporter.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/console_reporter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/console_reporter.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/console_reporter.cc > CMakeFiles/benchmark.dir/console_reporter.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/console_reporter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/console_reporter.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/console_reporter.cc -o CMakeFiles/benchmark.dir/console_reporter.cc.s

components/google_benchmark/src/CMakeFiles/benchmark.dir/counter.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/counter.cc.o: ../components/google_benchmark/src/counter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/counter.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/counter.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/counter.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/counter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/counter.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/counter.cc > CMakeFiles/benchmark.dir/counter.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/counter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/counter.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/counter.cc -o CMakeFiles/benchmark.dir/counter.cc.s

components/google_benchmark/src/CMakeFiles/benchmark.dir/csv_reporter.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/csv_reporter.cc.o: ../components/google_benchmark/src/csv_reporter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/csv_reporter.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/csv_reporter.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/csv_reporter.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/csv_reporter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/csv_reporter.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/csv_reporter.cc > CMakeFiles/benchmark.dir/csv_reporter.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/csv_reporter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/csv_reporter.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/csv_reporter.cc -o CMakeFiles/benchmark.dir/csv_reporter.cc.s

components/google_benchmark/src/CMakeFiles/benchmark.dir/json_reporter.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/json_reporter.cc.o: ../components/google_benchmark/src/json_reporter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/json_reporter.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/json_reporter.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/json_reporter.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/json_reporter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/json_reporter.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/json_reporter.cc > CMakeFiles/benchmark.dir/json_reporter.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/json_reporter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/json_reporter.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/json_reporter.cc -o CMakeFiles/benchmark.dir/json_reporter.cc.s

components/google_benchmark/src/CMakeFiles/benchmark.dir/reporter.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/reporter.cc.o: ../components/google_benchmark/src/reporter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/reporter.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/reporter.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/reporter.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/reporter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/reporter.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/reporter.cc > CMakeFiles/benchmark.dir/reporter.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/reporter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/reporter.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/reporter.cc -o CMakeFiles/benchmark.dir/reporter.cc.s

components/google_benchmark/src/CMakeFiles/benchmark.dir/sleep.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/sleep.cc.o: ../components/google_benchmark/src/sleep.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/sleep.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/sleep.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/sleep.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/sleep.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/sleep.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/sleep.cc > CMakeFiles/benchmark.dir/sleep.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/sleep.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/sleep.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/sleep.cc -o CMakeFiles/benchmark.dir/sleep.cc.s

components/google_benchmark/src/CMakeFiles/benchmark.dir/string_util.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/string_util.cc.o: ../components/google_benchmark/src/string_util.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/string_util.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/string_util.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/string_util.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/string_util.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/string_util.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/string_util.cc > CMakeFiles/benchmark.dir/string_util.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/string_util.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/string_util.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/string_util.cc -o CMakeFiles/benchmark.dir/string_util.cc.s

components/google_benchmark/src/CMakeFiles/benchmark.dir/sysinfo.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/sysinfo.cc.o: ../components/google_benchmark/src/sysinfo.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/sysinfo.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/sysinfo.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/sysinfo.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/sysinfo.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/sysinfo.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/sysinfo.cc > CMakeFiles/benchmark.dir/sysinfo.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/sysinfo.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/sysinfo.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/sysinfo.cc -o CMakeFiles/benchmark.dir/sysinfo.cc.s

components/google_benchmark/src/CMakeFiles/benchmark.dir/timers.cc.o: components/google_benchmark/src/CMakeFiles/benchmark.dir/flags.make
components/google_benchmark/src/CMakeFiles/benchmark.dir/timers.cc.o: ../components/google_benchmark/src/timers.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object components/google_benchmark/src/CMakeFiles/benchmark.dir/timers.cc.o"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/timers.cc.o -c /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/timers.cc

components/google_benchmark/src/CMakeFiles/benchmark.dir/timers.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/timers.cc.i"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/timers.cc > CMakeFiles/benchmark.dir/timers.cc.i

components/google_benchmark/src/CMakeFiles/benchmark.dir/timers.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/timers.cc.s"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src/timers.cc -o CMakeFiles/benchmark.dir/timers.cc.s

# Object files for target benchmark
benchmark_OBJECTS = \
"CMakeFiles/benchmark.dir/benchmark.cc.o" \
"CMakeFiles/benchmark.dir/benchmark_register.cc.o" \
"CMakeFiles/benchmark.dir/colorprint.cc.o" \
"CMakeFiles/benchmark.dir/commandlineflags.cc.o" \
"CMakeFiles/benchmark.dir/complexity.cc.o" \
"CMakeFiles/benchmark.dir/console_reporter.cc.o" \
"CMakeFiles/benchmark.dir/counter.cc.o" \
"CMakeFiles/benchmark.dir/csv_reporter.cc.o" \
"CMakeFiles/benchmark.dir/json_reporter.cc.o" \
"CMakeFiles/benchmark.dir/reporter.cc.o" \
"CMakeFiles/benchmark.dir/sleep.cc.o" \
"CMakeFiles/benchmark.dir/string_util.cc.o" \
"CMakeFiles/benchmark.dir/sysinfo.cc.o" \
"CMakeFiles/benchmark.dir/timers.cc.o"

# External object files for target benchmark
benchmark_EXTERNAL_OBJECTS =

components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/benchmark.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/benchmark_register.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/colorprint.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/commandlineflags.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/complexity.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/console_reporter.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/counter.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/csv_reporter.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/json_reporter.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/reporter.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/sleep.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/string_util.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/sysinfo.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/timers.cc.o
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/build.make
components/google_benchmark/src/libbenchmark.a: components/google_benchmark/src/CMakeFiles/benchmark.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/glauber/CLionProjects/wppGitHub/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX static library libbenchmark.a"
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && $(CMAKE_COMMAND) -P CMakeFiles/benchmark.dir/cmake_clean_target.cmake
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/benchmark.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
components/google_benchmark/src/CMakeFiles/benchmark.dir/build: components/google_benchmark/src/libbenchmark.a

.PHONY : components/google_benchmark/src/CMakeFiles/benchmark.dir/build

components/google_benchmark/src/CMakeFiles/benchmark.dir/clean:
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src && $(CMAKE_COMMAND) -P CMakeFiles/benchmark.dir/cmake_clean.cmake
.PHONY : components/google_benchmark/src/CMakeFiles/benchmark.dir/clean

components/google_benchmark/src/CMakeFiles/benchmark.dir/depend:
	cd /home/glauber/CLionProjects/wppGitHub/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/glauber/CLionProjects/wppGitHub /home/glauber/CLionProjects/wppGitHub/components/google_benchmark/src /home/glauber/CLionProjects/wppGitHub/cmake-build-debug /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src /home/glauber/CLionProjects/wppGitHub/cmake-build-debug/components/google_benchmark/src/CMakeFiles/benchmark.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : components/google_benchmark/src/CMakeFiles/benchmark.dir/depend

