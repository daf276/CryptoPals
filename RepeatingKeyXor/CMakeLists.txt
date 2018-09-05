cmake_minimum_required(VERSION 3.12)
project(RepeatingKeyXor)

set(CMAKE_CXX_STANDARD 17)

add_executable(RepeatingKeyXor main.cpp)
target_link_libraries(RepeatingKeyXor ${CMAKE_SOURCE_DIR}/lib/libHelperFunctions.dll.a)