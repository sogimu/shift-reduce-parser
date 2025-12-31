cmake_minimum_required(VERSION 3.6)
project(naive_stack_interpreter_unit_tests VERSION 0.0.1 LANGUAGES CXX)

# Enable AddressSanitizer
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Enabling AddressSanitizer")
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()

add_executable(${PROJECT_NAME}
    src/arithmetic_expression/arithmetic_test.cpp
    src/cfg/positive/arithmetic_expression/arithmetic_test.cpp
    src/cfg/positive/if_statment/if_test.cpp
    src/cfg/positive/scope_statment/scope_test.cpp
    src/main.cpp
)
target_link_libraries(${PROJECT_NAME} PUBLIC naive_stack_interpreter GTest::gtest_main)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
