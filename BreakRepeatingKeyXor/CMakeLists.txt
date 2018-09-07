cmake_minimum_required(VERSION 3.12)
project(BreakRepeatingKeyXor)

set(CMAKE_CXX_STANDARD 17)

add_executable(BreakRepeatingKeyXor main.cpp)
target_link_libraries(BreakRepeatingKeyXor ${CMAKE_SOURCE_DIR}/lib/libHelperFunctions.dll.a)