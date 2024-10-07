cmake_minimum_required(VERSION 3.0)
project(parser VERSION 0.0.1 LANGUAGES CXX)

add_executable(parser
    src/varible_store.h
    src/function_store.h
    src/calculator.h
    src/calculator.cpp
    src/main.cpp
)
target_link_libraries(parser PRIVATE shift-reduce-parser)
target_include_directories(parser PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(parser PRIVATE cxx_std_20)
