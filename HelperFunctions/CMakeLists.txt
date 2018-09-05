cmake_minimum_required(VERSION 3.12)
project(HelperFunctions)

set(CMAKE_CXX_STANDARD 17)

add_library(HelperFunctions SHARED Algorithms.h Algorithms.cpp Encodings.h Encodings.cpp)