cmake_minimum_required(VERSION 3.24)
project(Tucil2_13521136)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS -static)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-mrdrnd")

add_executable(Tucil2_13521136 src/main.cpp src/point.h src/rand.h src/sort.h src/plot.h src/plot.cpp)
set_target_properties(Tucil2_13521136 PROPERTIES LINKER_LANGUAGE CXX)