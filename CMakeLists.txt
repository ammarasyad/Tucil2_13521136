cmake_minimum_required(VERSION 3.24)
project(Tucil2_13521136)

#set(PYTHON_HEADERS /usr/include/python3.11)
#set(PYTHON_STATIC /usr/lib64)

#add_library(python3.11 SHARED IMPORTED GLOBAL)

#find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/include)
link_directories(${CMAKE_SOURCE_DIR}/src/lib)

#set_target_properties(python3.11 PROPERTIES
#        IMPORTED_LOCATION ${PYTHON_STATIC}/libpython3.11.so
#    INTERFACE_INCLUDE_DIRECTORIES ${PYTHON_HEADERS} LINKER_LANGUAGE C)
set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_EXE_LINKER_FLAGS -static)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-mrdrnd")

add_executable(Tucil2_13521136 src/main.cpp src/matplotlibcpp.h src/point.h src/rand.h src/sort.h)
set_target_properties(Tucil2_13521136 PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Tucil2_13521136 PUBLIC matplot)
#target_link_libraries(Tucil2_13521136 PUBLIC matplot PRIVATE python3.11 Python3::NumPy)
