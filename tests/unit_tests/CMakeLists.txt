cmake_minimum_required(VERSION 3.0)
project(unit_tests VERSION 0.0.1 LANGUAGES CXX)

# add_subdirectory(libs/Catch2)
add_subdirectory(libs/googletest)

add_executable(unit_tests
    src/lexical_tokens/arithmetic_expression/expression_in_circle_brackets_test.cpp
    src/lexical_tokens/arithmetic_expression/addition_test.cpp
    src/lexical_tokens/arithmetic_expression/subtraction_test.cpp
    src/lexical_tokens/arithmetic_expression/multiplication_test.cpp
    src/lexical_tokens/arithmetic_expression/division_test.cpp
    src/lexical_tokens/arithmetic_expression/varible_expression_test.cpp
    src/syntax_tree/arithmetic_expression/addition_test.cpp
    src/syntax_tree/arithmetic_expression/circle_brackets_test.cpp
    src/syntax_tree/if_expression/if_test.cpp
    src/syntax_tree/scope_expression/scope_test.cpp
    src/syntax_tree/varible_assign_expression/varible_assign_expression_test.cpp
    src/syntax_tree/print_expression/print_test.cpp
    src/syntax_tree_test.cpp
    src/syntax_tree_test.cpp
    # src/dfs_pre_order_range_test.cpp
    src/create_syntax_node_tree_test.cpp
    src/main.cpp
)
# target_link_libraries(unit_tests PRIVATE shift-reduce-parser Catch2::Catch2)
target_link_libraries(unit_tests PRIVATE shift-reduce-parser GTest::gtest_main)
target_include_directories(unit_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(unit_tests PRIVATE cxx_std_20)
