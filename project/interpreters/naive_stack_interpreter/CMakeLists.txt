cmake_minimum_required(VERSION 3.5)
project(naive_stack_interpreter VERSION 0.0.1 LANGUAGES CXX)

set(HEADERS
    include/varible_store.h
    include/function_store.h
    include/naive_stack_interpreter.h
)

set(SOURCES
    src/naive_stack_interpreter.cpp
)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
  "include" 
)

target_link_libraries(${PROJECT_NAME} PRIVATE parser )
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

add_subdirectory ("repl")
add_subdirectory ("tests/unit_tests")
