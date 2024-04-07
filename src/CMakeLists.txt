# add_custom_target(timer_h2
#   COMMAND cppfront-0.7.0 -verbose -emit-cppfront-info -import-std -pure-cpp2 timer.h2
#   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/cpp2
# )

include_directories(/home/rgc/u/include)
link_directories(/home/rgc/u/lib)

add_executable(bm_valarray bm_valarray.cpp)
target_link_libraries(bm_valarray benchmark gmock gtest)
# add_test(NAME bm_valarray COMMAND bm_valarray)

add_executable(spc1 sp_concurrency1.cpp)
add_executable(spc2 sp_concurrency2.cpp)
add_executable(spc3 sp_concurrency3.cpp)
