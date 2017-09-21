#######################################################
### SETTINGS                                        ###
#######################################################
cmake_minimum_required(VERSION 3.8)
project(markdown_reader)

set(CMAKE_CXX_STANDARD 14)

#######################################################
### EXTERNAL                                        ###
#######################################################
# Boost
set(Boost_USE_STATIC_LIBS ON)
set(boost_lib_names filesystem regex system iostreams date_time chrono timer thread coroutine log program_options serialization)
find_package(Boost REQUIRED COMPONENTS ${boost_lib_names})

# OpenCL
find_package(OpenCL REQUIRED)
include_directories(SYSTEM ${OpenCL_INCLUDE_DIRS})

# Gnuplot
find_package(Gnuplot REQUIRED)

#######################################################
### INCLUDES                                        ###
#######################################################
include_directories(${Boost_INCLUDE_DIR})
include_directories(include)

#######################################################
### EXECUTABLE BINARIES                             ###
#######################################################

# STREAMS
add_executable(util_termcolor tools/streams/termcolor.cpp)
add_executable(util_filesystem tools/streams/filesystem.cpp)
target_link_libraries(util_filesystem ${Boost_LIBRARIES})
add_executable(util_container_output tools/streams/container_output.cpp)
add_executable(util_iostreams tools/streams/iostreams.cpp)
target_link_libraries(util_iostreams ${Boost_LIBRARIES})
add_executable(util_text_table tools/streams/pretty_table.cpp)
add_executable(util_cout_plots tools/streams/cout_plots.cpp)
add_executable(util_gnuplot tools/streams/gnuplot.cpp)
target_link_libraries(util_gnuplot ${Boost_LIBRARIES})
add_executable(util_progress_bar tools/streams/progress_bar.cpp)
add_executable(util_logging tools/streams/logging.cpp)

# STRINGS / PARSERS
add_executable(util_strings tools/strings/strings.cpp)
add_executable(util_format tools/strings/format.cpp)
add_executable(util_tokenizer tools/strings/tokenizer.cpp)
add_executable(util_spirit_parser tools/strings/spirit_parser.cpp)
add_executable(util_spirit_grammar tools/strings/spirit_grammar.cpp)
add_executable(util_spirit_structure tools/strings/spirit_structure.cpp)

# CONTAINERS
add_executable(util_multi_index tools/containers/multi_index.cpp)
add_executable(util_bimap tools/containers/bimap.cpp)
add_executable(util_circularbuffer tools/containers/circularbuffer.cpp)
target_link_libraries(util_circularbuffer ${Boost_LIBRARIES})
add_executable(util_heap tools/containers/heap.cpp)
add_executable(util_multiarray tools/containers/multiarray.cpp)
add_executable(util_container tools/containers/container.cpp)
add_executable(util_graph tools/containers/graph.cpp)

# DATA STRUCTURES
add_executable(util_optional tools/data_structures/optional.cpp)
add_executable(util_any tools/data_structures/any.cpp)
add_executable(util_variant tools/data_structures/variant.cpp)
add_executable(util_propertytree tools/data_structures/propertytree.cpp)
add_executable(util_tribool tools/data_structures/tribool.cpp)
add_executable(util_json tools/data_structures/json.cpp)

# TIME
add_executable(util_datetime tools/time/datetime.cpp)
target_link_libraries(util_datetime ${Boost_LIBRARIES})
add_executable(util_chrono tools/time/chrono.cpp)
target_link_libraries(util_chrono ${Boost_LIBRARIES})
add_executable(util_timer tools/time/timer.cpp)
target_link_libraries(util_timer ${Boost_LIBRARIES})

# COMMUNICATION
add_executable(util_asio tools/communication/asio.cpp)
target_link_libraries(util_asio ${Boost_LIBRARIES})
add_executable(util_interprocess tools/communication/interprocess.cpp)
add_executable(util_simple_web_server tools/communication/simple_web_server.cpp)
target_link_libraries(util_simple_web_server ${Boost_LIBRARIES})

# MEMORY MANAGEMENT
add_executable(util_memory_pool tools/memory/memory_pool.cpp) # Manual Management
add_executable(util_flyweight_pattern tools/memory/flyweight_pattern.cpp) # Save memory when objects share data

# ALGORITHMS FOR:
add_executable(util_container_algorithms tools/algorithms/algorithms.cpp) # CONTAINER ALGORITHMS
add_executable(util_container_range tools/algorithms/range.cpp) # RANGE ALGORITHMS
target_link_libraries(util_container_range ${Boost_LIBRARIES})
add_executable(util_conversion tools/algorithms/conversion.cpp) # RANGE ALGORITHMS

# NUMERIC
add_executable(util_ublas_algebra tools/numeric/ublas.cpp)
add_executable(util_integers tools/numeric/integers.cpp)
add_executable(util_accumulators tools/numeric/accumulators.cpp)
add_executable(util_numeric_conversion tools/numeric/numeric_conversion.cpp)
add_executable(util_geometry tools/numeric/geometry.cpp)
add_executable(util_container_overload tools/helpers/container_overload.cpp)
add_executable(util_container_shortcuts tools/numeric/container_shortcuts.cpp)
add_executable(util_random_shortcuts tools/numeric/random_shortcuts.cpp)

# PARALLEL
add_executable(util_parallel_thread tools/parallel/parallel_thread.cpp)
target_link_libraries(util_parallel_thread ${Boost_LIBRARIES})
add_executable(util_parallel_lockfree tools/parallel/parallel_lockfree.cpp)
target_link_libraries(util_parallel_lockfree ${Boost_LIBRARIES})
add_executable(util_thread_pool tools/parallel/thread_pool.cpp)
add_executable(util_gpu tools/parallel/gpu.cpp)
target_link_libraries(util_gpu ${Boost_LIBRARIES} ${OpenCL_LIBRARIES})

# PROGRAMMING PARADIGMS
add_executable(util_functional_phoenix tools/programming_paradigms/functional_phoenix.cpp)
add_executable(util_generic_typetraits tools/programming_paradigms/generic_typetraits.cpp)
add_executable(util_generic_fusion_tuples tools/programming_paradigms/generic_fusion_tuples.cpp)
add_executable(util_coroutine tools/programming_paradigms/coroutine.cpp)
target_link_libraries(util_coroutine ${Boost_LIBRARIES})
add_executable(util_typestring tools/programming_paradigms/typestring.cpp)

# HELPERS
add_executable(util_boost_log tools/helpers/boost_log.cpp)
target_link_libraries(util_boost_log ${Boost_LIBRARIES})
add_executable(util_program_options tools/helpers/program_options.cpp)
target_link_libraries(util_program_options ${Boost_LIBRARIES})
add_executable(util_serialization tools/helpers/serialization.cpp)
target_link_libraries(util_serialization ${Boost_LIBRARIES})
add_executable(util_universally_unique_identifiers tools/helpers/universally_unique_identifiers.cpp)
add_executable(util_operators tools/helpers/operators.cpp)
add_executable(util_stl_shortcuts tools/helpers/stl_shortcuts.cpp)