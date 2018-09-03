# cmake_minimum_required(VERSION <specify CMake version here>)
project(ConvertHexToBase64)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(ConvertHexToBase64 Encodings.cpp Encodings.h)