cmake_minimum_required(VERSION 3.15)
project(Pftest VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(core)
add_subdirectory(Test)
add_subdirectory(Bench)

add_subdirectory(verification)
