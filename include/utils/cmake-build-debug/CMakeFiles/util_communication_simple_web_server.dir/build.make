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
include CMakeFiles/util_communication_simple_web_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/util_communication_simple_web_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/util_communication_simple_web_server.dir/flags.make

CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o: CMakeFiles/util_communication_simple_web_server.dir/flags.make
CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o: ../tools/communication/simple_web_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o -c /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/tools/communication/simple_web_server.cpp

CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/tools/communication/simple_web_server.cpp > CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.i

CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/tools/communication/simple_web_server.cpp -o CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.s

CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o.requires:

.PHONY : CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o.requires

CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o.provides: CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o.requires
	$(MAKE) -f CMakeFiles/util_communication_simple_web_server.dir/build.make CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o.provides.build
.PHONY : CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o.provides

CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o.provides.build: CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o


# Object files for target util_communication_simple_web_server
util_communication_simple_web_server_OBJECTS = \
"CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o"

# External object files for target util_communication_simple_web_server
util_communication_simple_web_server_EXTERNAL_OBJECTS =

util_communication_simple_web_server: CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o
util_communication_simple_web_server: CMakeFiles/util_communication_simple_web_server.dir/build.make
util_communication_simple_web_server: /usr/local/lib/libboost_filesystem-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_regex-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_system-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_iostreams-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_date_time-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_chrono-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_timer-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_thread-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_coroutine-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_log-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_program_options-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_serialization-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_atomic-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_context-mt.a
util_communication_simple_web_server: /usr/local/lib/libboost_log_setup-mt.a
util_communication_simple_web_server: CMakeFiles/util_communication_simple_web_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable util_communication_simple_web_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/util_communication_simple_web_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/util_communication_simple_web_server.dir/build: util_communication_simple_web_server

.PHONY : CMakeFiles/util_communication_simple_web_server.dir/build

CMakeFiles/util_communication_simple_web_server.dir/requires: CMakeFiles/util_communication_simple_web_server.dir/tools/communication/simple_web_server.cpp.o.requires

.PHONY : CMakeFiles/util_communication_simple_web_server.dir/requires

CMakeFiles/util_communication_simple_web_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/util_communication_simple_web_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/util_communication_simple_web_server.dir/clean

CMakeFiles/util_communication_simple_web_server.dir/depend:
	cd /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/include/utils/cmake-build-debug/CMakeFiles/util_communication_simple_web_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/util_communication_simple_web_server.dir/depend

