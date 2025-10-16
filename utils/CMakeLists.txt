add_library(BenchTest_utils
  src/timer.cpp)

target_include_directories(BenchTest_utils
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include)
