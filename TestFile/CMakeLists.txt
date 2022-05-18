cmake_minimum_required(VERSION 3.20)
project(FunctionGenerator)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)

add_executable(FunctionGenerator ${SOURCE_FILES})
include_directories(Function_lib)
add_subdirectory(Function_lib)
target_link_libraries(FunctionGenerator Function_lib)
add_subdirectory(Catch_tests)