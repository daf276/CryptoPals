cmake_minimum_required(VERSION 3.12)
project(HelperFunctions)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(HelperFunctions main.cpp Encodings.h Encodings.cpp Algorithms.cpp Algorithms.h)