cmake_minimum_required(VERSION 3.12)
project(FixedXor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(FixedXor FixedXor.cpp FixedXor.h ../ConvertHexToBase64/Encodings.h ../ConvertHexToBase64/Encodings.cpp)