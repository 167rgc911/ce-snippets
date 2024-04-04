# cmake_minimum_required(VERSION 3.28)
cmake_minimum_required(VERSION 3.16) # GH

project(ce-snippets CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# disable when using the full plethora of sanitizer options below
# set(CMAKE_CXX_CLANG_TIDY clang-tidy;-header-filter=.;-checks=-*,modernize-*)

add_compile_definitions(
    SOURCE_ROOT="${PROJECT_SOURCE_DIR}"
)

# valgrind does not work with sanitizers
# https://developers.redhat.com/blog/2021/05/05/memory-error-checking-in-c-and-c-comparing-sanitizers-and-valgrind
# gcc-7 NG
# add_compile_options(
#     "$<$<CONFIG:DEBUG>:-fsanitize=memory>"
# )
# gcc-7 NG w/ -fsanitize=address/kernel-address
# add_compile_options(
#     "$<$<CONFIG:DEBUG>:-fsanitize=thread>"
# )
add_compile_options(
    "$<$<CONFIG:DEBUG>:-fsanitize=undefined>"
)
add_compile_options(
    "$<$<CONFIG:DEBUG>:-fsanitize=address>"
)
# add_link_options(
#     "$<$<CONFIG:DEBUG>:-fsanitize=memory>"
# )
# add_link_options(
#     "$<$<CONFIG:DEBUG>:-fsanitize=thread>"
# )
add_link_options(
    "$<$<CONFIG:DEBUG>:-fsanitize=undefined>"
)
add_link_options(
    "$<$<CONFIG:DEBUG>:-fsanitize=address>"
)
# valgrind does not work with sanitizers

add_compile_options(
    "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
    "$<$<CONFIG:DEBUG>:-fno-omit-frame-pointer;-O0;-g3>"
)

# use Release build!
find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")
# use Release build!

# find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
# if (CMAKE_CXX_CPPCHECK)
#     list(
#         APPEND CMAKE_CXX_CPPCHECK
#             "--enable=warning"
#             "--inconclusive"
#             "--force"
#             "--inline-suppr"
#             "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
#     )
# endif()

# include(FetchContent)
# FetchContent_Populate(
#   cppfront
#   URL https://github.com/hsutter/cppfront/archive/refs/tags/v0.7.0.tar.gz
#   SOURCE_DIR cppfront
# )
# add_executable(cppfront-0.7.0 cppfront/source/cppfront.cpp)
# target_sources(
#   cppfront-0.7.0
#   PUBLIC
#   FILE_SET HEADERS
#   BASE_DIRS ${cppfront_SOURCE_DIR}/source
#   FILES ${cppfront_SOURCE_DIR}/source/common.h
#     ${cppfront_SOURCE_DIR}/source/io.h
#     ${cppfront_SOURCE_DIR}/source/lex.h
#     ${cppfront_SOURCE_DIR}/source/parse.h
#     ${cppfront_SOURCE_DIR}/source/reflect.h
#     ${cppfront_SOURCE_DIR}/source/sema.h
# )
# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest.git
#   GIT_TAG        f8d7d77c06936315286eb55f8de22cd23c188571 # release-1.14.0
#   OVERRIDE_FIND_PACKAGE
# )
# FetchContent_Declare(
#   googlebenchmark
#   GIT_REPOSITORY https://github.com/google/benchmark.git
#   GIT_TAG        344117638c8ff7e239044fd0fa7085839fc03021 # release-1.8.3
#   OVERRIDE_FIND_PACKAGE
# )
# FetchContent_Declare(
#   Catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG        8ac8190e494a381072c89f5e161b92a08d98b37b # v3.5.3
#   OVERRIDE_FIND_PACKAGE
# )
find_package(GTest PATHS $ENV[HOME]/u/lib/cmake/GTest)
find_package(benchmark PATHS $ENV[HOME]/u/lib/cmake/benchmark)
find_package(Catch2 PATHS $ENV[HOME]/u/lib/cmake/Catch2)

include_directories(include)
# include_directories(${cppfront_SOURCE_DIR}/include)

add_subdirectory(src)

# include(CTest)
