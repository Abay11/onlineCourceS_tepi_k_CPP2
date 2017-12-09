cmake_minimum_required(VERSION 3.8)
project(StepicCPPLessons)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES 5_3_16metaprogramming.cpp)

add_executable(StepicCPPLessons ${SOURCE_FILES})
target_link_libraries(StepicCPPLessons -lpthread)