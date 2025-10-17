add_library(BenchTest_core
  src/utils/timer.cpp
  src/detail/case_impl.cpp
  src/types.cpp)

target_include_directories(BenchTest_core
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include)
