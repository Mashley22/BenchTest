include(${CMAKE_CURRENT_LIST_DIR}/cmake/BenchTestAddTest.cmake)

add_library(BenchTest_Test
  src/Case_env.cpp
  src/fail.cpp
  src/Suite.cpp
)

target_include_directories(BenchTest_Test
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(BenchTest_Test
  PUBLIC
    BenchTest_core
)
