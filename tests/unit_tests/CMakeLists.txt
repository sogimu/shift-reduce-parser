cmake_minimum_required(VERSION 3.6)
project(unit_tests VERSION 0.0.1 LANGUAGES CXX)

# set(CMAKE_C_COMPILER "/usr/bin/clang")
# set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_subdirectory(libs/googletest)

add_executable(unit_tests
    src/lexical_tokens/arithmetic_expression/expression_in_circle_brackets_test.cpp
    src/lexical_tokens/arithmetic_expression/addition_test.cpp
    src/lexical_tokens/arithmetic_expression/subtraction_test.cpp
    src/lexical_tokens/arithmetic_expression/multiplication_test.cpp
    src/lexical_tokens/arithmetic_expression/division_test.cpp
    src/lexical_tokens/arithmetic_expression/varible_expression_test.cpp
    src/syntax_tree/arithmetic_expression/arithmetic_test.cpp
    src/syntax_tree/conditional_expression/conditional_expression_test.cpp
    src/syntax_tree/if_statment/if_test.cpp
    src/syntax_tree/while_statment/while_test.cpp
    src/syntax_tree/function_statment/function_statment_test.cpp
    src/syntax_tree/function_call/function_call_test.cpp
    src/syntax_tree/scope_statment/scope_test.cpp
    src/syntax_tree/varible_assign_expression/varible_assign_expression_test.cpp
    src/syntax_tree/print_statment/print_statment_test.cpp
    src/syntax_tree/return_statment/return_statment_test.cpp
    src/syntax_tree_test.cpp
    # src/dfs_pre_order_range_test.cpp
    src/create_syntax_node_tree_test.cpp
    src/main.cpp
)
target_link_libraries(unit_tests PRIVATE shift-reduce-parser GTest::gtest_main)
target_include_directories(unit_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(unit_tests PRIVATE cxx_std_20)
