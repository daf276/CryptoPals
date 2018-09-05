cmake_minimum_required(VERSION 3.12)
project(DetectSingleCharacterXOR)

set(CMAKE_CXX_STANDARD 17)

add_executable(DetectSingleCharacterXOR main.cpp)
target_link_libraries(DetectSingleCharacterXOR ${CMAKE_SOURCE_DIR}/lib/libHelperFunctions.dll.a)