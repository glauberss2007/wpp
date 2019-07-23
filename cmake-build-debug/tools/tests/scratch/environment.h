//
// Created by Alan de Freitas on 01/06/17.
//

#ifndef SOLVER_COMPILER_SETTINGS_H
#define SOLVER_COMPILER_SETTINGS_H

namespace environment {
    // ad hoc

    // locations
    inline const char* project_binary_dir = "/home/glauber/CLionProjects/wppcopy2/cmake-build-debug";
    inline const char* cmake_binary_dir = "/home/glauber/CLionProjects/wppcopy2/cmake-build-debug";
    inline const char* cmake_current_binary_dir = "/home/glauber/CLionProjects/wppcopy2/cmake-build-debug/tools/tests/scratch";
    inline const char* project_source_dir = "/home/glauber/CLionProjects/wppcopy2";
    inline const char* cmake_source_dir = "/home/glauber/CLionProjects/wppcopy2";
    inline const char* cmake_current_source_dir = "/home/glauber/CLionProjects/wppcopy2/tools/tests/scratch";

    inline const char* CMAKE_BINARY_DIR = "/home/glauber/CLionProjects/wppcopy2/cmake-build-debug";
    inline const char* CMAKE_COMMAND = "/snap/clion/52/bin/cmake/bin/cmake";
    inline const char* CMAKE_CURRENT_BINARY_DIR = "/home/glauber/CLionProjects/wppcopy2/cmake-build-debug/tools/tests/scratch";
    inline const char* CMAKE_CURRENT_LIST_FILE = "/home/glauber/CLionProjects/wppcopy2/tools/tests/scratch/CMakeLists.txt";
    inline const char* CMAKE_CURRENT_LIST_DIR = "/home/glauber/CLionProjects/wppcopy2/tools/tests/scratch";
    inline const char* CMAKE_CURRENT_LIST_LINE = "";
    inline const char* CMAKE_CURRENT_SOURCE_DIR = "/home/glauber/CLionProjects/wppcopy2/tools/tests/scratch";
    inline const char* CMAKE_FILES_DIRECTORY = "/CMakeFiles";
    inline const char* CMAKE_MODULE_PATH = "/home/glauber/CLionProjects/wppcopy2/cmake;/home/glauber/CLionProjects/wppcopy2/components/cmake/Modules/";
    inline const char* CMAKE_ROOT = "/snap/clion/52/bin/cmake/share/cmake-3.10";
    inline const char* CMAKE_SOURCE_DIR = "/home/glauber/CLionProjects/wppcopy2";
    inline const char* EXECUTABLE_OUTPUT_PATH = "";
    inline const char* LIBRARY_OUTPUT_PATH = "";
    inline const char* PROJECT_NAME = "wpp";
    inline const char* CMAKE_PROJECT_NAME = "wpp";
    inline const char* PROJECT_BINARY_DIR = "/home/glauber/CLionProjects/wppcopy2/cmake-build-debug";
    inline const char* PROJECT_SOURCE_DIR = "/home/glauber/CLionProjects/wppcopy2";

    // Environment Variables
    inline const char* CMAKE_INCLUDE_PATH = "";
    inline const char* CMAKE_LIBRARY_PATH = "";
    inline const char* CMAKE_PREFIX_PATH = "";
    inline const char* CMAKE_INSTALL_ALWAYS = "";
    inline const char* DESTDIR = "";

    // System & Compiler Information
    inline const char* CMAKE_MAJOR_VERSION = "3";
    inline const char* CMAKE_MINOR_VERSION = "10";
    inline const char* CMAKE_PATCH_VERSION = "3";
    inline const char* CMAKE_TWEAK_VERSION = "0";
    inline const char* CMAKE_VERSION = "3.10.3";
    inline const char* CMAKE_SYSTEM = "Linux-4.15.0-43-generic";
    inline const char* CMAKE_SYSTEM_NAME = "Linux";
    inline const char* CMAKE_SYSTEM_VERSION = "4.15.0-43-generic";
    inline const char* CMAKE_SYSTEM_PROCESSOR = "x86_64";
    inline const char* CMAKE_GENERATOR = "Unix Makefiles";
    inline const bool UNIX = 01;
    inline const bool WIN32 = 0;
    inline const bool APPLE = 0;
    inline const bool MINGW = 0;
    inline const bool MSYS = 0;
    inline const bool CYGWIN = 0;
    inline const bool BORLAND = 0;
    inline const bool WATCOM = 0;
    inline const bool MSVC = 0;
    inline const bool MSVC_IDE = 0;
    inline const bool MSVC60 = 0;
    inline const bool MSVC70 = 0;
    inline const bool MSVC71 = 0;
    inline const bool MSVC80 = 0;
    inline const bool CMAKE_COMPILER_2005 = 0;
    inline const bool MSVC90 = 0;
    inline const bool MSVC10 = 0;
    inline const char* CMAKE_C_COMPILER_ID = "GNU";
    inline const char* CMAKE_CXX_COMPILER_ID = "GNU";
    inline const bool CMAKE_COMPILER_IS_GNUCC = 01;
    inline const bool CMAKE_COMPILER_IS_GNUCXX = 01;

    // Various Options
    inline const char* CMAKE_SKIP_RULE_DEPENDENCY = "";
    inline const char* CMAKE_SKIP_INSTALL_ALL_DEPENDENCY = "";
    inline const char* CMAKE_SKIP_RPATH = "NO";
    inline const char* CMAKE_INCLUDE_CURRENT_DIR = "";
    inline const char* CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE = "";
    inline const char* CMAKE_VERBOSE_MAKEFILE = "FALSE";
    inline const char* CMAKE_SUPPRESS_REGENERATION = "";
    inline const char* CMAKE_COLOR_MAKEFILE = "ON";
    inline const char* CMAKE_SKIP_PREPROCESSED_SOURCE_RULES = "";
    inline const char* CMAKE_SKIP_ASSEMBLY_SOURCE_RULES = "";
    inline const char* CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS = "";

    // Compilers and Tools
    inline const char* BUILD_SHARED_LIBS = "OFF";
    inline const char* CMAKE_AR = "/usr/bin/ar";
    inline const char* CMAKE_BUILD_TYPE = "Debug";
    inline const char* CMAKE_CONFIGURATION_TYPES = "";
    inline const char* CMAKE_C_COMPILER = "/usr/bin/cc";
    inline const char* CMAKE_C_FLAGS = "";
    inline const char* CMAKE_C_FLAGS_DEBUG = "-g";
    inline const char* CMAKE_C_FLAGS_RELEASE = "-O3 -DNDEBUG";
    inline const char* CMAKE_C_FLAGS_RELWITHDEBINFO = "-O2 -g -DNDEBUG";
    inline const char* CMAKE_CFG_INTDIR = ".";
    inline const char* CMAKE_CXX_COMPILER = "/usr/bin/c++";
    inline const char* CMAKE_CXX_FLAGS = "";
    inline const char* CMAKE_CXX_FLAGS_DEBUG = "-g";
    inline const char* CMAKE_CXX_FLAGS_RELEASE = "-O3 -DNDEBUG";
    inline const char* CMAKE_CXX_FLAGS_RELWITHDEBINFO = "-O2 -g -DNDEBUG";
    inline const char* CMAKE_RANLIB = "/usr/bin/ranlib";
    inline const char* CMAKE_SHARED_LINKER_FLAGS = "";

    // Prefixes, Suffixes (Postfixes), and Extensions
    inline const char* CMAKE_C_IGNORE_EXTENSIONS = "h;H;o;O;obj;OBJ;def;DEF;rc;RC";
    inline const char* CMAKE_C_OUTPUT_EXTENSION = ".o";
    inline const char* CMAKE_C_SOURCE_FILE_EXTENSIONS = "c;m";
    inline const char* CMAKE_CXX_IGNORE_EXTENSIONS = "inl;h;hpp;HPP;H;o;O;obj;OBJ;def;DEF;rc;RC";
    inline const char* CMAKE_CXX_OUTPUT_EXTENSION = ".o";
    inline const char* CMAKE_CXX_SOURCE_FILE_EXTENSIONS = "C;M;c++;cc;cpp;cxx;mm;CPP";
    inline const char* CMAKE_EXECUTABLE_SUFFIX = "";
    inline const char* CMAKE_FIND_LIBRARY_PREFIXES = "lib";
    inline const char* CMAKE_FIND_LIBRARY_SUFFIXES = ".so;.a";
    inline const char* CMAKE_IMPORT_LIBRARY_PREFIX = "";
    inline const char* CMAKE_IMPORT_LIBRARY_SUFFIX = "";
    inline const char* CMAKE_LINK_LIBRARY_SUFFIX = "";
    inline const char* CMAKE_RC_OUTPUT_EXTENSION = "";
    inline const char* CMAKE_RC_SOURCE_FILE_EXTENSIONS = "";
    inline const char* CMAKE_SHARED_LIBRARY_PREFIX = "lib";
    inline const char* CMAKE_SHARED_LIBRARY_SUFFIX = ".so";
    inline const char* CMAKE_SHARED_MODULE_PREFIX = "lib";
    inline const char* CMAKE_SHARED_MODULE_SUFFIX = ".so";
    inline const char* CMAKE_STATIC_LIBRARY_PREFIX = "lib";
    inline const char* CMAKE_STATIC_LIBRARY_SUFFIX = ".a";
    inline const char* CMAKE_DEBUG_POSTFIX = "";
    inline const char* CMAKE_RELEASE_POSTFIX = "";
    inline const char* CMAKE_config_POSTFIX = "";

    // Build rules
    inline const char* CMAKE_CXX_CREATE_SHARED_LIBRARY = "<CMAKE_CXX_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <SONAME_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>";
    inline const char* CMAKE_CXX_CREATE_SHARED_MODULE = "<CMAKE_CXX_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <SONAME_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>";
    inline const char* CMAKE_CXX_CREATE_STATIC_LIBRARY = "";
    inline const char* CMAKE_CXX_COMPILE_OBJECT = "<CMAKE_CXX_COMPILER>  <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>";
    inline const char* CMAKE_CXX_LINK_EXECUTABLE = "<CMAKE_CXX_COMPILER>  <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>";
    inline const char* CMAKE_C_CREATE_SHARED_LIBRARY = "<CMAKE_C_COMPILER> <CMAKE_SHARED_LIBRARY_C_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS> <SONAME_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>";
    inline const char* CMAKE_C_CREATE_SHARED_MODULE = "<CMAKE_C_COMPILER> <CMAKE_SHARED_LIBRARY_C_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS> <SONAME_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>";
    inline const char* CMAKE_C_CREATE_STATIC_LIBRARY = "";
    inline const char* CMAKE_C_COMPILE_OBJECT = "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT>   -c <SOURCE>";
    inline const char* CMAKE_C_LINK_EXECUTABLE = "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>";

    // Expansion Rules
    inline const char* ASSEMBLY_SOURCE = "";
    inline const char* FLAGS = "";
    inline const char* LANGUAGE_COMPILE_FLAGS = "";
    inline const char* LINK_FLAGS = "";
    inline const char* LINK_LIBRARIES = "";
    inline const char* OBJECT = "";
    inline const char* OBJECTS = "";
    inline const char* OBJECTS_QUOTED = "";
    inline const char* OBJECT_DIR = "";
    inline const char* PREPROCESSED_SOURCE = "";
    inline const char* SOURCE = "";
    inline const char* TARGET = "";
    inline const char* TARGET_BASE = "";
    inline const char* TARGET_IMPLIB = "";
    inline const char* TARGET_INSTALLNAME_DIR = "";
    inline const char* TARGET_PDB = "";
    inline const char* TARGET_QUOTED = "";
    inline const char* TARGET_SONAME = "";
    inline const char* TARGET_VERSION_MAJOR = "";
    inline const char* TARGET_VERSION_MINOR = "";
}

#endif //SOLVER_COMPILER_SETTINGS_H
