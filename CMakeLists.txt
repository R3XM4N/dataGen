cmake_minimum_required(VERSION 3.10)
project(RDataGen)

#C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#including hpps
include_directories(${CMAKE_SOURCE_DIR}/include)

#building the test
add_executable(RDataGenTest examples/main.cpp)