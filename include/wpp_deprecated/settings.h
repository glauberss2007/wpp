#pragma once
#ifndef SOLVER_COMPILER_SETTINGS_H
#define SOLVER_COMPILER_SETTINGS_H

namespace wpp_settings {
    // ad hoc
    const int   wpp_log_level = 01;
    const bool  enable_debug = 01;
    const bool  enable_logging = 01;
    const bool  enable_ssl = 01;
    const char opening_tag = '{';
    const char closing_tag = '}';
    #if __cplusplus >= 201402L
        const bool  cpp14 = true;
    #else
        const bool  cpp14 = false;
    #endif

    namespace cmake {
        // locations
        const char* CMAKE_BINARY_DIR = "/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/cmake-build-debug";
        const char* CMAKE_COMMAND = "/Applications/CLion.app/Contents/bin/cmake/bin/cmake";
        const char* CMAKE_CURRENT_BINARY_DIR = "/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/cmake-build-debug";
        const char* CMAKE_CURRENT_LIST_FILE = "/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/CMakeLists.txt";
        const char* CMAKE_CURRENT_LIST_DIR = "/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp";
        const char* CMAKE_CURRENT_LIST_LINE = "";
        const char* CMAKE_CURRENT_SOURCE_DIR = "/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp";
        const char* CMAKE_FILES_DIRECTORY = "/CMakeFiles";
        const char* CMAKE_MODULE_PATH = "/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/cmake;/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/components/cmake/Modules/";
        const char* CMAKE_ROOT = "/Applications/CLion.app/Contents/bin/cmake/share/cmake-3.8";
        const char* CMAKE_SOURCE_DIR = "/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp";
        const char* EXECUTABLE_OUTPUT_PATH = "";
        const char* LIBRARY_OUTPUT_PATH = "";
        const char* PROJECT_NAME = "wpp";
        const char* CMAKE_PROJECT_NAME = "wpp";
        const char* PROJECT_BINARY_DIR = "/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/cmake-build-debug";
        const char* PROJECT_SOURCE_DIR = "/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp";

        // Environment Variables
        const char* CMAKE_INCLUDE_PATH = "";
        const char* CMAKE_LIBRARY_PATH = "";
        const char* CMAKE_PREFIX_PATH = "";
        const char* CMAKE_INSTALL_ALWAYS = "";
        const char* DESTDIR = "";

        // System & Compiler Information
        const char* CMAKE_MAJOR_VERSION = "3";
        const char* CMAKE_MINOR_VERSION = "8";
        const char* CMAKE_PATCH_VERSION = "2";
        const char* CMAKE_TWEAK_VERSION = "0";
        const char* CMAKE_VERSION = "3.8.2";
        const char* CMAKE_SYSTEM = "Darwin-16.7.0";
        const char* CMAKE_SYSTEM_NAME = "Darwin";
        const char* CMAKE_SYSTEM_VERSION = "16.7.0";
        const char* CMAKE_SYSTEM_PROCESSOR = "x86_64";
        const char* CMAKE_GENERATOR = "Unix Makefiles";
        const bool UNIX = 01;
        const bool WIN32 = 0;
        const bool APPLE = 01;
        const bool MINGW = 0;
        const bool MSYS = 0;
        const bool CYGWIN = 0;
        const bool BORLAND = 0;
        const bool WATCOM = 0;
        const bool MSVC = 0;
        const bool MSVC_IDE = 0;
        const bool MSVC60 = 0;
        const bool MSVC70 = 0;
        const bool MSVC71 = 0;
        const bool MSVC80 = 0;
        const bool CMAKE_COMPILER_2005 = 0;
        const bool MSVC90 = 0;
        const bool MSVC10 = 0;
        const char* CMAKE_C_COMPILER_ID = "AppleClang";
        const char* CMAKE_CXX_COMPILER_ID = "AppleClang";
        const bool CMAKE_COMPILER_IS_GNUCC = 0;
        const bool CMAKE_COMPILER_IS_GNUCXX = 0;

        // Various Options
        const char* CMAKE_SKIP_RULE_DEPENDENCY = "";
        const char* CMAKE_SKIP_INSTALL_ALL_DEPENDENCY = "";
        const char* CMAKE_SKIP_RPATH = "NO";
        const char* CMAKE_INCLUDE_CURRENT_DIR = "";
        const char* CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE = "";
        const char* CMAKE_VERBOSE_MAKEFILE = "FALSE";
        const char* CMAKE_SUPPRESS_REGENERATION = "";
        const char* CMAKE_COLOR_MAKEFILE = "ON";
        const char* CMAKE_SKIP_PREPROCESSED_SOURCE_RULES = "";
        const char* CMAKE_SKIP_ASSEMBLY_SOURCE_RULES = "";
        const char* CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS = "";

        // Compilers and Tools
        const char* BUILD_SHARED_LIBS = "";
        const char* CMAKE_AR = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ar";
        const char* CMAKE_BUILD_TYPE = "Debug";
        const char* CMAKE_CONFIGURATION_TYPES = "";
        const char* CMAKE_C_COMPILER = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc";
        const char* CMAKE_C_FLAGS = "";
        const char* CMAKE_C_FLAGS_DEBUG = "-g";
        const char* CMAKE_C_FLAGS_RELEASE = "-O3 -DNDEBUG";
        const char* CMAKE_C_FLAGS_RELWITHDEBINFO = "-O2 -g -DNDEBUG";
        const char* CMAKE_CFG_INTDIR = ".";
        const char* CMAKE_CXX_COMPILER = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++";
        const char* CMAKE_CXX_FLAGS = "";
        const char* CMAKE_CXX_FLAGS_DEBUG = "-g";
        const char* CMAKE_CXX_FLAGS_RELEASE = "-O3 -DNDEBUG";
        const char* CMAKE_CXX_FLAGS_RELWITHDEBINFO = "-O2 -g -DNDEBUG";
        const char* CMAKE_RANLIB = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib";
        const char* CMAKE_SHARED_LINKER_FLAGS = "";

        // Prefixes, Suffixes (Postfixes), and Extensions
        const char* CMAKE_C_IGNORE_EXTENSIONS = "h;H;o;O;obj;OBJ;def;DEF;rc;RC";
        const char* CMAKE_C_OUTPUT_EXTENSION = ".o";
        const char* CMAKE_C_SOURCE_FILE_EXTENSIONS = "c;m";
        const char* CMAKE_CXX_IGNORE_EXTENSIONS = "inl;h;hpp;HPP;H;o;O;obj;OBJ;def;DEF;rc;RC";
        const char* CMAKE_CXX_OUTPUT_EXTENSION = ".o";
        const char* CMAKE_CXX_SOURCE_FILE_EXTENSIONS = "C;M;c++;cc;cpp;cxx;mm;CPP";
        const char* CMAKE_EXECUTABLE_SUFFIX = "";
        const char* CMAKE_FIND_LIBRARY_PREFIXES = "lib";
        const char* CMAKE_FIND_LIBRARY_SUFFIXES = ".tbd;.dylib;.so;.a";
        const char* CMAKE_IMPORT_LIBRARY_PREFIX = "";
        const char* CMAKE_IMPORT_LIBRARY_SUFFIX = "";
        const char* CMAKE_LINK_LIBRARY_SUFFIX = "";
        const char* CMAKE_RC_OUTPUT_EXTENSION = "";
        const char* CMAKE_RC_SOURCE_FILE_EXTENSIONS = "";
        const char* CMAKE_SHARED_LIBRARY_PREFIX = "lib";
        const char* CMAKE_SHARED_LIBRARY_SUFFIX = ".dylib";
        const char* CMAKE_SHARED_MODULE_PREFIX = "lib";
        const char* CMAKE_SHARED_MODULE_SUFFIX = ".so";
        const char* CMAKE_STATIC_LIBRARY_PREFIX = "lib";
        const char* CMAKE_STATIC_LIBRARY_SUFFIX = ".a";
        const char* CMAKE_DEBUG_POSTFIX = "";
        const char* CMAKE_RELEASE_POSTFIX = "";
        const char* CMAKE_config_POSTFIX = "";

        // Build rules
        const char* CMAKE_CXX_CREATE_SHARED_LIBRARY = "<CMAKE_CXX_COMPILER> <LANGUAGE_COMPILE_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <LINK_FLAGS> -o <TARGET> <SONAME_FLAG> <TARGET_INSTALLNAME_DIR><TARGET_SONAME> <OBJECTS> <LINK_LIBRARIES>";
        const char* CMAKE_CXX_CREATE_SHARED_MODULE = "<CMAKE_CXX_COMPILER> <LANGUAGE_COMPILE_FLAGS> <CMAKE_SHARED_MODULE_CREATE_CXX_FLAGS> <LINK_FLAGS> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>";
        const char* CMAKE_CXX_CREATE_STATIC_LIBRARY = "";
        const char* CMAKE_CXX_COMPILE_OBJECT = "<CMAKE_CXX_COMPILER>  <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>";
        const char* CMAKE_CXX_LINK_EXECUTABLE = "<CMAKE_CXX_COMPILER>  <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>";
        const char* CMAKE_C_CREATE_SHARED_LIBRARY = "<CMAKE_C_COMPILER> <LANGUAGE_COMPILE_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS> <LINK_FLAGS> -o <TARGET> <SONAME_FLAG> <TARGET_INSTALLNAME_DIR><TARGET_SONAME> <OBJECTS> <LINK_LIBRARIES>";
        const char* CMAKE_C_CREATE_SHARED_MODULE = "<CMAKE_C_COMPILER>  <LANGUAGE_COMPILE_FLAGS> <CMAKE_SHARED_MODULE_CREATE_C_FLAGS> <LINK_FLAGS> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>";
        const char* CMAKE_C_CREATE_STATIC_LIBRARY = "";
        const char* CMAKE_C_COMPILE_OBJECT = "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT>   -c <SOURCE>";
        const char* CMAKE_C_LINK_EXECUTABLE = "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>";

        // Expansion Rules
        const char* ASSEMBLY_SOURCE = "";
        const char* FLAGS = "";
        const char* LANGUAGE_COMPILE_FLAGS = "";
        const char* LINK_FLAGS = "";
        const char* LINK_LIBRARIES = "";
        const char* OBJECT = "";
        const char* OBJECTS = "";
        const char* OBJECTS_QUOTED = "";
        const char* OBJECT_DIR = "";
        const char* PREPROCESSED_SOURCE = "";
        const char* SOURCE = "";
        const char* TARGET = "";
        const char* TARGET_BASE = "";
        const char* TARGET_IMPLIB = "";
        const char* TARGET_INSTALLNAME_DIR = "";
        const char* TARGET_PDB = "";
        const char* TARGET_QUOTED = "";
        const char* TARGET_SONAME = "";
        const char* TARGET_VERSION_MAJOR = "";
        const char* TARGET_VERSION_MINOR = "";
    }
}

#endif //SOLVER_COMPILER_SETTINGS_H

/* #ifdef - enables debug mode */
#define CROW_ENABLE_DEBUG
/* #undef  */

/* #ifdef - enables logging */
#define CROW_ENABLE_LOGGING
/* #undef  */

/* #ifdef - enables ssl */
//#define CROW_ENABLE_SSL
/* #undef  */

/* #define - specifies log level */
/*
    Debug       = 0
    Info        = 1
    Warning     = 2
    Error       = 3
    Critical    = 4

    default to INFO
*/
#define CROW_LOG_LEVEL 1
/* #undef  */

// compiler flags
#if __cplusplus >= 201402L
#define CROW_CAN_USE_CPP14
#endif

#if defined(_MSC_VER)
#if _MSC_VER < 1900
#define CROW_MSVC_WORKAROUND
#define constexpr const
#define noexcept throw()
#endif
#endif
