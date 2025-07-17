cmake_minimum_required(VERSION 3.8)
project(rust_cpp_interop)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(math_cpp)

add_executable(rust_cpp_interop main.cpp)

target_link_libraries(rust_cpp_interop math_cpp)