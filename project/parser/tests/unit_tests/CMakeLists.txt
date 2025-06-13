cmake_minimum_required(VERSION 3.6)
project(parser_unit_tests VERSION 0.0.1 LANGUAGES CXX)

# Enable AddressSanitizer
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Enabling AddressSanitizer")
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()

add_executable(${PROJECT_NAME}
    src/lexical_tokens/arithmetic_expression/expression_in_circle_brackets_test.cpp
    src/lexical_tokens/arithmetic_expression/addition_test.cpp
    src/lexical_tokens/arithmetic_expression/subtraction_test.cpp
    src/lexical_tokens/arithmetic_expression/multiplication_test.cpp
    src/lexical_tokens/arithmetic_expression/division_test.cpp
    src/lexical_tokens/arithmetic_expression/varible_expression_test.cpp
    src/syntax_tree/arithmetic_expression/arithmetic_test.cpp
    src/syntax_tree/if_statment/if_test.cpp
    src/syntax_tree/while_statment/while_test.cpp
    src/syntax_tree/function_statment/function_statment_test.cpp
    src/syntax_tree/function_call/function_call_test.cpp
    src/syntax_tree/scope_statment/scope_test.cpp
    src/syntax_tree/varible_assign_expression/varible_assign_expression_test.cpp
    src/syntax_tree/print_statment/print_statment_test.cpp
    src/syntax_tree/return_statment/return_statment_test.cpp
    src/create_syntax_node_tree_test.cpp
    src/main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE parser GTest::gtest_main nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
