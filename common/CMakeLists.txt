add_library(BenchTest_common
  src/utils/timer.cpp)

target_include_directories(BenchTest_common
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include)
