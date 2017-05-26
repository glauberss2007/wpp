# Basic setup

## Project data

> Instructions for basic use of CMake

```cmake
cmake_minimum_required(VERSION 3.6)
project(cmake_experiments)
```

Specifying the languages used by it:

```cmake
project(cmake_experiments [CXX] [C] [Java] [NONE])
```

CXX and C are the default.

Define version

```cmake
set(cmake_VERSION_MAJOR 1)
set(cmake_VERSION_MINOR 0)
```

## Define compiler

1) Generator defines the compiler

    * List of compilers on `Modules/CMakeDetermineCCompiler.cmake` and `Modules/CMakeDetermineCXXCompiler.cmake`

2) An environment variable defined before CMAKE is run

    * `CC` defines `C` compiler. `CXX` defines `C++` compiler. Command => `DCMAKE_CXX_COMPILER=cl`

3) A cache entry (not recommended because some tests might have been run on the compiler)

`CMAKE_CXX_COMPILER` and `CMAKE_C_COMPILER`

### Define Standard
`set(CMAKE_CXX_STANDARD 14)`

# Define Source files

`set(SOURCE_FILES main.cpp)`

## Properties of source files
`set_source_files_properties()`

Common properties: `COMPILE_FLAGS`, `GENERATED`, `OBJECT_DEPENDS`, `ABSTRACT`, `WRAP_EXCLUDE`

## Depending on the operating system

(`WIN32` calls WinMain instead of main)

```cmake
if (WIN32)
    set(SOURCE_FILES ${SOURCE_FILES} winsupport.cpp)
else ()
    set(SOURCE_FILES ${SOURCE_FILES} unixsupport.cpp)
endif ()
```

# Variables

All variables are sent to functions, subdirectories and includes by value.

```cmake
set(FOO 1)
set(FOO 0)
set(items_to_buy apple orange pear beer)
foreach(item ${items_to_buy})
    message("Don't forget to buy one ${item}")
endforeach()
option (USE_JPEG "Do you want to use the JPEG library?") # option is kept on cache
message("Use JPEG library: ${USE_JPEG}")
```

# Flow Control

## Conditional

```cmake
if (FOO)
    # do something
elseif (BAR)
    # do sth
else ()
    # do sth
endif ()
```

Relational operators:

* `AND`
* `OR`
* `NOT`
* `COMMAND command-name`
* `DEFINED variable`
* `EXISTS file-name`
* `EXISTS directory-name`
* `IS_DIRECTORY name`
* `IS_ABSOLUTE name`
* `name1 IS_NEWER_THAN name2`
* `variable MATCHES regex`
* `string MATCHES regex`
* `EQUAL`
* `LESS`
* `GREATER`
* `STRLESS`
* `STREQUAL`
* `STRGREATER`
* `VERSION_LESS`
* `VERSION_EQUAL`
* `VERSION_GREATER`

## Repetition

```cmake
foreach (tfile
        TestAnison
        TestButter
        TestBest
        TestCityBlock
        TestConvolve
        )
    add_test(${tfile}-image ${VTK_EXECUTABLE}
        ${VTK_SOURCE_DIR}/Tests/rtImageTest.tcl
        ${VTK_SOURCE_DIR}/Tests/${tfile}.tcl
        -D ${VTK_DATA_ROOT}
        -V Baseline/Imaging/${tfile}.png
        -A ${VTK_SOURCE_DIR}/Wrapping/Tcl
    )
endforeach (tfile)
```


## Functions
```cmake
function (foo)
    message(${test})
    set(test 2)
    message(${test})
    set(test 2 PARENT_SCOPE)
    message(${test})
endfunction()
```

# Directories, generators, tests, properties
`add_subdirectory(dir)`

## Properties for directories
`ADDITIONAL_MAKE_CLEAN_FILES`, `EXCLUDE_FROM_ALL`, `LISTFILE_STACK`
`set_property` and `get_property`

## include and run commands in another file
`include(file1.cmake)`

# Targets

* Cria executável:
`add_executable(cmake_experiments ${SOURCE_FILES})`
* Cria biblioteca que pode ser usada no código (STATIC`, SHARED or MODULE):
`add_library(cmake_experiments_dll STATIC ${SOURCE_FILES})`
* Cria target:
`add_custom_target`

### Editar propriedades de targets (most common is link_flags)
`set_target_properties(cmake_experiments)`

# Bibliotecas para linkar com o target
`target_link_libraries(cmake_experiments_dll cmake_experiments_dll)`

### Libraries
Look for library under different names and folders

```cmake
find_library(TCL_LIBRARY
        NAMES tcl tcl84 tcl83 tcl82 tcl80
        PATHS /usr/lib /usr/local/lib
        )
```

Link if found `TCL_LIBRARY`

```cmake
if (TCL_LIBRARY)
    target_link_libraries(cmake_experiments ${TCL_LIBRARY})
endif ()
```

# Build Configuration

`CMAKE_BUILD_TYPE`

* `Debug`: debug flags on
* `Release`: basic optimizations on
* `MinSizeRel`: smallest code
* `RelWithDebInfo`: optimized with debug information

# Instalation

The `install(TARGETS ...)` command tells how the software is to be installed. A common use is:

```cmake
install(TARGETS targets...
    DESTINATION <dir>
    EXPORT <export name>
    )
```

The signatures are:

* `install(TARGETS target1 target2...)`: targets of the script
* `install(FILES file1 file2...)`: general-purpose (header files, documentation, or data files)
* `install(DIRECTORY directory1 directory2...)`: install entire directory tree. Install directories with resources (icons, images, etc).
* `install(PROGRAMS ...)`: same as FILES but default permission include the executable bit
* `install(SCRIPT ...)`: user provided cmake script file to be executed during installation. Usually for pre or post-install actions.
* `install(CODE ...)`: user provided cmake code to be executed during installation. Similar to SCRIPT but code is provided inline.

Keywords and arguments:

* `DESTINATION`: location of the files (default is /usr/local/ or <Drive>/Program Files/<Project>
* `PERMISSIONS`: <OWNER|GROUP|WORLD>_<READ|WRITE|EXECUTE>
* `CONFIGURATIONS`: for which the rules apply
* `COMPONENT`: for which rules apply (Runtime, Documentation, Development, etc)
* `OPTIONAL`: Defines that it's not an error if the file to be installed does not exist.



# Modules

Files for code reuse. In the Modules folder of Cmake. Can be used with the include command.

```cmake
include(FindTLC)

target_link_libraries(FOO ${TCL_LIBRARY})
```

CMake will look for modules in default folders.

## Types of modules

* Find modules (ex: `include(FindPNG)`). Normally use:
    * Find header in one of the folders: `find_path(VARIABLE header folder1 folder2)`
    * Find library in one of the folders: `find_library(VARIABLE lib folder1 folder2)`
* System Introspection Modules. Return variables about the environment.
* Utility Modules. Help to compare projects, debug, etc.

# System Inspection

## Look for includes and libraries

For most C++ libraries:

* `find_library` locates or allows user to locate a library. The library suffix can be lib, dll or any other.

```cmake
find_library(TIFF_LIBRARY
    NAMES tiff tiff2
    PATHS /usr/local/lib /usr/lib
    )
# ...
target_link_libraries(myprogram ${TIFF_LIBRARY})
```

* `find_path`: finds the path to a representative include file

```cmake
find_path(TIFF_INCLUDES tiff.h
    /usr/local/include
    /usr/include
    )
# ...
include_directories(${TIFF_INCLUDES})
```

But also:
* `find_file`
* `find_program`

### Look for packages

* `find_package(<Package> [version])`: used for libraries used as building blocks for other projects. `find_package` has two modes:
    * `Module` mode: searches for a `find-module`: a file named `Find<Package>.cmake`. Looks first in `CMAKE_MODULE_PATH` and the in CMake installation. If it's found, it looks for individual components.
    * `Config` mode: it enters this mode after failing to locate the library. It searches for a package configuration file: `<Package>Config.cmake`. or `<package>-config.cmake`.

The `<XX>_FOUND` exists in every module. Conventions for other variables from `find_package`:

* `<XX>_INCLUDE_DIRS`: where to find the include directories
* `<XX>_LIBRARIES`: where to find the libraries to link (if it is a library)
* `<XX>_DEFINITIONS`: preprocessor definitions to use
* `<XX>_EXECUTABLE`: where to find the `<XX>` tool
* `<XX>_<YY>_EXECUTABLE`: where to find the `<YY>` tool that comes with `<XX>`
* `<XX>_ROOT_DIR`: base directory
* `<XX>_VERSION_<YY>`: if version `<YY>` was found
* `<XX>_<YY>_FOUND`: if the part `<YY>` of `<XX>` is available
* `<XX>_FOUND`: if we found `<XX>`

`find_package(OpenGL)` is equivalent to `include(${CMAKE_ROOT}/Modules/FindOpenGL.cmake)` or `include(FindOpenGL)`.

## Look for functions in the system

To test if the system has a `foobar` function by default, create a test program:

```cpp
// testNeedFoobar.cpp

#include <foobar.h>

int main(){
    foobar();
}
```

```cmake
# testNeedFoobar.cmake

try_compile(HAS_FOOBAR_CALL
    ${CMAKE_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/testNeedFoobar.c
    )
```

Now we can use `add_definitions` to run the test and save the result.

Sometimes we need to test and run to test a result:

```cpp
// TestByteOrder.cpp

int main(){
    // Are the most significant byte first or last?
    union {
        long l;
        char c[sizeof (long)];
    } u;
    u.l = 1;
    exit (u.c[sizeof (long) - 1] == 1);
}
```

```cmake
# TestByteOrder.cmake

try_run(RUN_RESULT_VAR
    COMPILE_RESULT_VAR
    ${CMAKE_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/Modules/TestByteOrder.cpp
    OUTPUT_VARIABLE OUTPUT
    )
```

The result of the test will go into `RUN_RESULT_VAR`, result of the compile into `COMPILE_RESULT_VAR`, and any output in `OUTPUT`.

For small test programs, the `FILE` and `WRITE` commands can be used:

```cmake
file (WRITE
    ${CMAKE_BINARY_DIR}/CMakeTmp/testCCompiler.c
    "int main(){return 0;}"
    })

try_compile (CMAKE_C_COMPILER_WORKS
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/CMakeTmp/testCCompiler.c
    OUTPUT_VARIABLE OUTPUT
    )
```

Pre-defined `try_run` and `try_compile` macros:

* `CheckFunctionExists.cmake`: checks if C function is on the system
* `CheckIncludeFile.cmake`: checks for Include file on the system
* `CheckIncludeFileCXX.cmake`: checks for Include file in a C++ program on the system
* `CheckIncludeFiles.cmake`: checks for a group of Include files on the system
* `CheckLibraryExists.cmake`: checks if a library exists
* `CheckSymbolExists.cmake`: checks if a symbol exists in a header
* `CheckTypeSize.cmake`: checks size in bytes of a variable type
* `CheckVariableExists.cmake`: checks if a global variable exists

## Passing the parameters to compilation

### Passing the parameters on compile time

`add_definitions` commands:

```cmake
option (DEBUG_BUILD
    "Build with extra debug print message.")

if (DEBUG_BUILD)
    add_definitions (-DDEBUG_BUILD)
endif()
```

```cpp
#ifdef DEBUG_BUILD
    printf("the value of v is %d", v);
#endif
```

#### Fine tuning the parameters

Another way is to set or append property of folder, source or target:

```cmake
add_library(mylib src1.c src2.c)
add_executable(myexe main1.c)
# property included on all folders
set_property(
    DIRECTORY
    APPEND PROPERTY COMPILE_DEFINITIONS A AV=1
    )
# property in the library
set_property(
    TARGET mylib
    APPEND PROPERTY COMPILE_DEFINITIONS B BV=2
    )
# property on the source file
set_property(
    SOURCE src1.c
    APPEND PROPERTY COMPILE_DEFINITIONS C CV=3
    )
# property in the library only in debug mode
set_property(
    TARGET mylib
    APPEND PROPERTY COMPILE_DEFINITIONS_DEBUG B BV=2
    )
```

### Passing the parameters on a preconfigured header

Better option most times because another application might need these parameters.

The `configure_file` command need an input where the variables will be are expanded or replaced:

```cmake
configure_file(
    ${PROJECT_SOURCE_DIR}/projectConfigure.h.in
    ${PROJECT_BINARY_DIR}/projectConfigure.h)
include_directories(${PROJECT_BINARY_DIR})
```

```c++
// projectConfigure.h.in
#cmakedefine HAS_FOOBAR_CALL
#define PROJECT_BINARY_DIR "${PROJECT_BINARY_DIR}"
```



Notation:

```cpp
#cmakedefine VARIABLE
```

Gets replaced, if VARIABLE is true, by

```cpp
#define VARIABLE
```

Gets replaced, if VARIABLE is false, by

```cpp
/* #undef VARIABLE /*
```

`${VARIABLE}` or `@VARIABLE@` get replaced by the value of VARIABLE.

# Package Configuration Files

Files so other applications can find the project.

```cmake
# Start of CMakeLists.txt
cmake_minumim_required(VERSION 2.6.3)
project(Gromit C)
set(version 1.0)
# ...
# Building targets
add_library(gromit STATIC gromit.c gromit.h)
add_executable(gromit-gen gromit-gen.c)
# ...
# Install gromit and export targets for outside projects
install(FILES gromit.h DESTINATION include/gromit-${version})
install(TARGETS gromit gromit-gen
    DESTINATION lib/gromit-${version}
    EXPORT gromit-targets)
install(EXPORT gromit-targets
    DESTINATION lib/gromit-${version})
# ...
# Create a package configuration file in installation tree so other packages can find it with find_package
configure_file(
    ${Gromit_SOURCE_DIR}/pkg/gromit-config.cmake.in
    ${Gromit_BINARY_DIR}/pkg/gromit-config.cmake @ONLY)
configure_file(
    ${Gromit_SOURCE_DIR}/pkg/gromit-config-version.cmake.in
    ${Gromit_BINARY_DIR}/pkg/gromit-config-version.cmake @ONLY)
install(FILES ${Gromit_BINARY_DIR}/pkg/gromit-config.cmake
    ${Gromit_BINARY_DIR}/gromit-config-version.cmake
    DESTINATION lib/gromit-${version})
```

In the `gromit-config.cmake.in` file:

```cmake
# Compute the installation prefix relative to this file
get_filename_component(_dir "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_prefix "${_dir}/../.." ABSOLUTE)

# Import the target
include("${_prefix}/lib/gromit-@version@/gromit-targets.cmake")

# Report other information
set(gromit_INCLUDE_DIRS "${_prefix}/include/gromit-@version@")
```

After installation, `gromit-config.cmake.in` knows the location of other installed files. The package version file `gromit-config-version.cmake.in` has code like:

```cmake
set(PACKAGE_VERSION "@version@")
if (NOT "${PACKAGE_FIND_VERSION}" VERSION_GREATER "@version@")
    set(PACKAGE_VERSION_COMPATIBLE 1) # compatible with older
    if ("${PACKAGE_FIND_VERSION}" VERSION_EQUAL "@version@")
        set(PACKAGE_VERSION_EXACT 1) # exact match for this version
    endif ()
endif ()
```

An application that uses the package can do:

```cmake
cmake_minimum_required(VERSION 2.6.3)
project(MyProject C)

find_package(gromit 1.0 REQUIRED)
include_directories(${gromit_INCLUDE_DIRS})
# run imported executable
add_custom_command(OUTPUT generated.c
                    COMMAND gromit-gen generated.c)
add_executable(myexe generated.c)
target_link_libraries(myexe gromit) #link to imported library
```

If `find_package` works, `gromit-config.cmake` has been loaded so `gromit` targets have been imported and variables such as `gromit_INCLUDE_DIRS` have been defined.

If the package configuration will be in the `build` tree instead of `installation` tree, `gromit`'s CMake File should have:

```cmake
# Make project useable from build tree
export (TARGETS gromit gromit-gen FILE gromit-targets.cmake)
configure_file(${gromit_SOURCE_DIR}/gromit-config.cmake.in
        ${gromit_BINARY_DIR}/gromit-config.cmake @ONLY)
```

This `gromit-config.cmake.in` will have:

```cmake
# Import the targets
include("@Gromit_BINARY_DIR@/gromit-target.cmake")

# Report other information
set(gromit_INCLUDE_DIRS "@Gromit_SOURCE_DIR@")
```

# Custom Commands and Targets

When there are additional tasks to compiling (compile documentation, generating source files, generating files in general, moving files, post processing, etc).

## Portability

Copy/add/move-ing files in cross platform way. The option `-E` (execute), makes cmake work as a general cross-platform utility command. Some of the commands that follow `-E` are:

* `chdir dir command args`: changes current directory to `dir` and execute the command `command` with the arguments `args` 
* `copy file destination`: copies `file` from current directory to `destination` 
* `copy_if_different in-file out-file`: checks if the 2 files are different before copying them. 
* `copy_directory source destination`: copy source dir to destination dir with all subfolders 
* `remove file1 file2 ...`: removes a list of files 
* `echo string`: prints a message 
* `time command args`: runs the command and times its execution 

Besides commands, there are platform specific variables:

* `EXE_EXTENSION`: Executable extension in the system (.exe or maybe nothing)
* `CMAKE_CFG_INTDIR`: Enviroment based on build type
* `CMAKE_CURRENT_BINARY_DIR`: Current binary directory
* `CMAKE_CURRENT_SOURCE_DIR`: Current source directory
* `EXECUTABLE_OUTPUT_PATH`: Some projects have this directory for all executables
* `LIBRARY_OUTPUT_PATH`: Some projects have this directory for all libraries

## Add custom command to a target
 
`add_custom_command` adds a rule to `makefile` or build step to Visual Studio. When adding a custom command to a target we use:
 
```cmake
add_custom_command(
    TARGET target
    PRE_BUILD | PRE_LINK | POST_BUILD
    COMMAND command [ARGS arg1 arg2 arg3 ...]
    [COMMAND command [ARGS arg1 arg2 arg3 ...] ...]
    [COMMENT comment]    
    )
```

Choose when the command is run:
`PRE_BUILD`: before any other dependencies are built
`PRE_LINK`: after all dependencies are built but before the actual link command
`POST_BUILD`: after the target has been built

Copying an executable after it has been built:

```cmake
# define executable
add_executable(Foo bar.c)

# get where it will be located
get_target_property(EXE_LOC Foo LOCATION)

# add custom command to copy it
add_custom_command(
    TARGET Foo
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${EXE_LOC} /testing_department/files
    )
```

The command to be execute is simply `cmake` (`cmake`'s full path is `${CMAKE_COMMAND}`). The arguments indicate to copy from `${EXE_LOC}` to `/testing_department/files`. `TARGET` accepts `foo` but `copy` needs the full path `${EXE_LOC}`.
 
## Custom command to generate file

Rule to construct an output file. This rule will replace any rules for building this file:

```cmake
add_custom_command(OUTPUT output1 [output2 output3...]
    COMMAND command [ARGS arg1 arg2 arg3 ...]
    [COMMAND command [ARGS arg1 arg2 arg3 ...] ...]
    [MAIN_DEPENDENCY depend]
    [DEPENDS [depends...]]
    [COMMENT comment]    
    )
```

`OUTPUT` is the file that will result from running the command. `COMMAND`s will be executed with its `ARGS`. `DEPENDS` are executables and files on which the `COMMAND` depends. If the dependencies change, the command will re-execute. The `MAIN_DEPENDENCY` is an optional dependency that should not be a `.cpp` or `.c` because it would override the build rule for the file.
 
To add an executable that will create source files:
 
```cmake
# creator executable is built
add_executable(creator creator.cxx)

get_target_property(creator EXE_LOC LOCATION)

# custom command to produce created.c
add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/created.c
    DEPENDS creator
    COMMAND ${EXE_LOC}
    ARGS ${PROJECT_BINARY_DIR}/created.c
)

# add an executable that uses created.c
add_executable(Foo ${PROJECT_BINARY_DIR}/created.c)
```

The result `OUTPUT` is writen to the binary tree. The executable `Foo` is built using created.c.

## Custom targets

If the end product is not an executable or a library (documentation, run tests, update web pages). The signature is:

```cmake
add_custom_target( name [ALL]
    [command arg arg arg ...]
    [DEPENDS depends depends depends ...]
    )
```

`ALL` specifies that it'll be built with the `ALL_BUILD` target. The commands as arguments are optional and executed post-build. Sometimes it will depend on other files, or `DEPENDS`.

To run Java Archiver to create Foo.jar.

```cmake
add_custom_target( FooJAR ALL
    ${JAR} -cvf "\"${PROJECT_BINARY_DIR}/Foo.jar\""
                "\"${PROJECT_SOURCE_DIR}/Java\""
                )
```

To run latex:

```cmake
# Build dvi from tex
add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/doc1.dvi
    DEPENDS ${PROJECT_SOURCE_DIR}/doc1.tex
    COMMAND ${LATEX}
    ARGS ${PROJECT_SOURCE_DIR}/doc1.tex
)

# Produce pdf from dvi
add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/doc1.pdf
    DEPENDS ${PROJECT_BINARY_DIR}/doc1.dvi
    COMMAND ${DVIPDF}
    ARGS ${PROJECT_BINARY_DIR}/doc1.dvi
)

# add custom target that generated pdf file
add_custom_target( TDocument ALL
    DEPENDS ${PROJECT_BINARY_DIR}/doc1.pdf
)
```

The target `TDocument` checks if all its dependencies are built (`doc1.pdf`). If not, the custom commands will be called. The `custom_command` can be reduced by:

```cmake
# Build pdf from tex
add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/doc1.pdf
    DEPENDS ${PROJECT_SOURCE_DIR}/doc1.tex
    COMMAND ${LATEX}
    ARGS ${PROJECT_SOURCE_DIR}/doc1.tex
    COMMAND ${DVIPDF}
    ARGS ${PROJECT_BINARY_DIR}/doc1.dvi
)

# add custom target that generated pdf file
add_custom_target( TDocument ALL
    DEPENDS ${PROJECT_BINARY_DIR}/doc1.pdf
)
```

If there are many documents:

```cmake
# List of docs
set(DOCS doc1 doc2 doc3)

foreach (DOC ${DOCS})
    
    # Build pdf from tex
    add_custom_command(
        OUTPUT ${PROJECT_BINARY_DIR}/${DOC}.pdf
        DEPENDS ${PROJECT_SOURCE_DIR}/${DOC}.tex
        COMMAND ${LATEX}
        ARGS ${PROJECT_SOURCE_DIR}/${DOC}.tex
        COMMAND ${DVIPDF}
        ARGS ${PROJECT_BINARY_DIR}/${DOC}.dvi
    )
    
    # List of generated docs
    set(DOCS_RESULTS ${DOC_RESULTS}
        ${PROJECT_BINARY_DIR}/${DOC}.pdf
    )
    
endforeach()

# add custom target that generated pdf file
add_custom_target( TDocument ALL
    DEPENDS ${DOC_RESULTS}
)
```
> Dependencies and outputs should always have the full path (such as `${PROJECT_BINARY_DIR}/foo.h`), unless it's a target dependency.

# Converting to CMake

## Directory structure

```cmake
# set sources from subdirectories
set (SOURCES
    subdir1/foo.cxx
    subdir1/foo2.cxx
    subdir2/gah.cxx
    subdir2/bar.cxx
)
# let the subdirectory build and then target
add_subdirectory(subdir1)
add_executable(program main.ccp)
target_link_libraries(program target_fromsubdir1)
# including modules from subdirectories
include(subdir1/CMakeLists.txt)
foreach(FILE ${FILES})
    set (subdir1Files ${subdir1Files} subdir1/${FILE})
endforeach()
add_executable(program main.ccp subdir1Files)
```

## Build directory

Defined in the variables `EXECUTABLE_OUTPUT_PATH` and `LIBRARY_OUTPUT_PATH`.

### Useful commands

```cmake
file(GLOB SRC_FILES *.cxx)
add_executable(foo ${SRC_FILES})
```
* `file` matches all files with an expression
* `make_directory` creates directory
* `exec_program` executes a program. Useful to convert linux `autoconf` files.

## From Unix Makefiles

Create a matching CMake file.

```makefile
OBJS = \
    foo.o \
    foo2.o \
    foo3.o
```

becomes

```cmake
set(SOURCES
    foo.c
    foo2.c
    foo3.c
    )
```

## From autoconf projects

They consist of 3 pieces: `configure.in` file drives the process, `Makefile.in` becomes the final `Makefile`, and remaining configuring files.

The `Makefile.in` can be converted as usual unix makefiles. For `configure.in`, most macros have corresponding commands in CMake:

* `AC_ARG_WITH` => `option`
* `AC_CHECK_HEADER` => `CHECK_INCLUDE_FILE` from `CheckIncludeFile` module
* `AC_MSG_CHECKING` => `message` with the `STATUS` argument
* `AC_SUBST` => automatically in the `configure_file` command
* `AC_CHECK_LIB` => `CHECK_LIBRARY_EXISTS` from `CheckLibraryExists` module
* `AC_CONFIG_SUBDIRS` => `add_subdirectory` command
* `AC_OUTPUT` => `configure_file` command
* `AC_TRY_COMPILE` => `try_compile` command

## Converting from windows workspaces

Add all source files and directories to `CMakeLists.txt`.

# Cross Compiling

## Toolchain files

In order to cross compile, CMake has to be informed of the target platform via a `toolchain` file, which describes everything to know about the target platform. For instance, for compiling Windows MinGW under Linux:
 
```cmake
# TC-mingw.cmake
# The name of the system
set(CMAKE_SYSTEM_NAME Windows)
# which compilers to use
set(CMAKE_C_COMPILER i586-mingw32msvc-gcc)
set(CMAKE_CXX_COMPILER i586-mingw32msvc-g++)
# default behaviour of find_XXX() - search in the host
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# search headers and libraries in the target enviroment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```

Then we set the toolchain variable `CMAKE_TOOLCHAIN_FILE`:

```
cmake -DCMAKE_TOOLCHAIN_FILE=~/TC-mingw.cmake ... 
```

The variables to be defined are: 

* Properties of the system
    * `CMAKE_SYSTEM_NAME`: set it to the same value it would have been set y cmake on the target platform `Linux`, `Windows`, `Generic`. Changing this variable makes `CMAKE_CROSSCOMPILING` become `TRUE`.
    * `CMAKE_SYSTEM_VERSION`: optional and unused
    * `CMAKE_SYSTEM_PROCESSOR`: optional
* Compiler
    * `CMAKE_C_COMPILER`: cmake can' guess the target system and it can't guess the compiler.
    * `CMAKE_CXX_COMPILER`: C++ compiler
* Finding packages (host packages are useless)
    * `CMAKE_FIND_ROOT_PATH_MODE`: search directories
    * `CMAKE_FIND_ROOT_PATH_MODE_PROGRAM`: behaviour of `find_program` (`NEVER`, `ONLY`, or `BOTH`)
    * `CMAKE_FIND_ROOT_PATH_MODE_LIBRARY`: behaviour of `find_library`
    * `CMAKE_FIND_ROOT_PATH_MODE_INCLUDE`: behaviour of `find_path` and `find_file`

The current platform can be tested with `WIN32`, `UNIX`, `APPLE`. If crosscompiling, the host plataform is `CMAKE_HOST_WIN32`, `CMAKE_HOST_UNIX`, `CMAKE_HOST_APPLE`.

# Packaging with CPack

Creates two types of packages: 

* Source Package: Makes a copy of the src tree in a zip file.
* Binary Package: Tied to the install commands.

Simples exemple only needs to include CPack module:

```cmake
project(CoolStuff)
add_executable(coolstuff coolstuff.cxx)
install(TARGETS coolstuff RUNTIME DESTINATION bin)
include(CPack)
```

Including CPack adds the targets `package` and `package_source` to the project (or `PACKAGE` for Visual Studio):

```bash
mkdir build
cd build
cmake ../CoolStuff
make
make package
make package_source
```

# Automation and Testing

Types of test

* Compiling test: simplest smoke test
* Regression test: if results kept the same. More difficult to create.
* Black box test: exercise units of code without knowledge of how they work. Testing general functions of the public API.
* White box test: exercise units of code with knowledge of how they work. Stress potential failure in the code.
* Software standard compliance: if the software adhere to standards of the project. If all classes have a method, if all methods have a certain prefix, etc.

The tests can run the software or run another tool on the source. To add a test:

```cmake
add_test(TestName ExecutableToRun arg1 arg2 arg3 ...)
```

`add_test` takes a string for the name, the executable (`${EXECUTABLE_OUTPUT_PATH}/TestInstatiator). All tests are called with `make test` target.

A test passes if:
* Executable was found
* The test ran without exception
* Exited with return code 0

That can be changed with environment variables:

```cmake
set_property(TEST test_name
        PROPERTY prop1 prop2 prop3
        )
```

Properties:
* `ENVIRONMENT`
* `LABELS`
* `WILL_FAIL`
* `PASS_REGULAR_EXPRESSION`: test output of the test
* `FAIL_REGULAR_EXPRESSION`: test output against expression

# Porting to new platforms

CMake runs these procedures:

* The platform (host and target) is determined
    * `CMAKE_HOST_SYSTEM_NAME`
    * `CMAKE_HOST_SYSTEM_VERSION`
    * `CMAKE_HOST_SYSTEM_PROCESSOR`
    * `CMAKE_HOST_SYSTEM` => `${CMAKE_HOST_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_VERSION}`
    * `CMAKE_SYSTEM_NAME`
    * `CMAKE_SYSTEM_VERSION`
    * `CMAKE_SYSTEM_PROCESSOR`
    * `CMAKE_SYSTEM` => `${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_VERSION}`
* Enable all languages specified in the `project` command
    * `CMakeDetermine(LANG)Compiler.cmake` is run for each language
        * It discovers compiler and tools
    * CMake also tries to compile some code `CMake(LANG)CompilerId.(LANG_SUFFIX)`
    * CMake configures `CMake(LANG)Compiler.cmake.in` into `CMake(LANG)Compiler.cmake` 
    * Run `CMakeSystemSpecificInformation.cmake`
        * It calls `${CMAKE_SYSTEM_NAME}.cmake` (Ex.: `SunOS.cmake`)
    * Call `CMake(Lang)Information.cmake` for each `LANG`
        * It contains default rules for creating targets
        * It loads `${CMAKE_SYSTEM_NAME}-${COMPILER_ID}-LANG-${CMAKE_SYSTEM_PROCESSOR}.cmake` if it exists
            * This file is intended only for cross-compiling
        * It loads `${CMAKE_SYSTEM_NAME}-${COMPILER_ID}-LANG.cmake`
         
To define a new platform we need a `Platform/${CMAKE_SYSTEM_NAME}.cmake` file. Depending on the tools, you can also create `Platform/${CMAKE_SYSTEM_NAME}-${COMPILER_BASE_NAME}.cmake`

To add a new language (`add_library` and `add_executable` can be used for a new language), 4 files have to be defined:
* `CMakeDetermine(LANG)Compiler.cmake`: finds path to the compiler
* `CMake(LANG)Compiler.cmake.in`: input for a configure call
* `CMakeTest(LANG)Compiler.cmake`: try compile to make sure it's working
* `CMake(LANG)Information.cmake`: sets rules for LANG
    * `CMAKE_(LANG)_CREATE_SHARED_LIBRARY`
    * `CMAKE_(LANG)_CREATE_SHARED_MODULE`
    * `CMAKE_(LANG)_CREATE_STATIC_LIBRARY`
    * `CMAKE_(LANG)_COMPILE_OBJECT`
    * `CMAKE_(LANG)_LINK_EXECUTABLE`
    
The rules are defined by strings of the kind `set(CMAKE_(LANG)_LINK_EXECUTABLE tag1 tag2 tag3 etc)`. Valid tags are `<TARGET>`, `<TARGET_QUOTED>`, `<TARGET_BASE>`, `<TARGET_SONAME>`, `<OBJECTS>`, `<OBJECTS_QUOTED>`, `<OBJECT>`, `<LINK_LIBRARIES>`, `<FLAGS>`, `<LINK_FLAGS>`, `<SOURCE>`, or language specific tags such as `<CMAKE_(LANG)_COMPILER>`, `<CMAKE_SHARED_LIBRARY_CREATE_(LANG)_FLAGS>`, `<CMAKE_SHARED_MODULE_CREATE_(LANG)_FLAGS>`, `<CMAKE_(LANG)_LINK_FLAGS>`,`<CMAKE_AR>`,`<CMAKE_RANLIB>`

