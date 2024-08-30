cmake_minimum_required(VERSION 3.5)
project(shift-reduce-parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    include/utils/dfs_pre_order_range.h
    include/enums.h
    include/lexical_tokens.h
    include/syntax_tree.h
    include/utils.h
    include/i_grammar.h
    include/i_syntax_node.h
    include/i_syntax_node_visitor.h
    include/syntax_node_empty_visitor.h
    include/syntax_node_state_machine_visitor.h
    include/grammars/base/bol_syntax_node.h
    include/grammars/base/eol_syntax_node.h
    include/grammars/base/plus_syntax_node.h
    include/grammars/base/minus_syntax_node.h
    include/grammars/base/asterisk_syntax_node.h
    include/grammars/base/slash_syntax_node.h
    include/grammars/base/number_syntax_node.h
    include/grammars/base/f_syntax_node.h
    include/grammars/base/semicolon_syntax_node.h
    include/grammars/base/print_syntax_node.h
    include/grammars/base/equal_syntax_node.h
    include/grammars/base/less_syntax_node.h
    include/grammars/base/more_syntax_node.h
    include/grammars/base/open_curly_bracket_syntax_node.h
    include/grammars/base/close_curly_bracket_syntax_node.h
    include/grammars/base/open_circle_bracket_syntax_node.h
    include/grammars/base/close_circle_bracket_syntax_node.h
    include/grammars/base/if_syntax_node.h
    include/grammars/base/name_syntax_node.h
    include/grammars/base/comma_syntax_node.h
    include/grammars/addition/addition_syntax_node.h
    include/grammars/subtraction/subtraction_syntax_node.h
    include/grammars/division/division_syntax_node.h
    include/grammars/expression_syntax_node.h
    include/grammars/scope_syntax_node.h
    include/grammars/f_grammar.h
    include/grammars/conditional_expression_syntax_node.h
    include/grammars/conditional_expression_grammar.h
    include/grammars/print_expression_syntax_node.h
    include/grammars/print_expression_grammar.h
    include/grammars/if_expression_syntax_node.h
    include/grammars/if_expression_grammar.h
    include/grammars/function_syntax_node.h
    include/grammars/function_call_syntax_node.h
    include/grammars/while_expression_syntax_node.h
    include/grammars/while_expression_grammar.h
    include/grammars/varible_assigment_syntax_node.h
    include/grammars/expression_grammar.h
    include/grammars/varible_assigment_grammar.h
    include/grammars/computational_expression_syntax_node.h
    include/grammars/computational_expression_grammar.h
    include/grammars/scope_grammar.h
    include/grammars/function_grammar.h
    include/grammars/function_call_grammar.h
)

set(SOURCES
    src/lexical_tokens.cpp
    src/grammars/base/plus_syntax_node.cpp
    src/grammars/base/minus_syntax_node.cpp
    src/grammars/base/asterisk_syntax_node.cpp
    src/grammars/base/slash_syntax_node.cpp
    src/grammars/base/bol_syntax_node.cpp
    src/grammars/base/eol_syntax_node.cpp
    src/grammars/base/number_syntax_node.cpp
    src/grammars/base/f_syntax_node.cpp
    src/grammars/base/semicolon_syntax_node.cpp
    src/grammars/base/comma_syntax_node.cpp
    src/grammars/base/print_syntax_node.cpp
    src/grammars/base/equal_syntax_node.cpp
    src/grammars/base/less_syntax_node.cpp
    src/grammars/base/more_syntax_node.cpp
    src/grammars/base/open_curly_bracket_syntax_node.cpp
    src/grammars/base/close_curly_bracket_syntax_node.cpp
    src/grammars/base/open_circle_bracket_syntax_node.cpp
    src/grammars/base/close_circle_bracket_syntax_node.cpp
    src/grammars/base/if_syntax_node.cpp
    src/grammars/base/while_syntax_node.cpp
    src/grammars/base/while_syntax_node.cpp
    src/grammars/base/name_syntax_node.cpp
    src/grammars/addition/addition_syntax_node.cpp
    src/grammars/subtraction/subtraction_syntax_node.cpp
    src/grammars/multiply/multiply_syntax_node.cpp
    src/grammars/division/division_syntax_node.cpp
    src/grammars/computational_expression_syntax_node.cpp
    src/grammars/expression_syntax_node.cpp
    src/grammars/print_expression_syntax_node.cpp
    src/grammars/if_expression_syntax_node.cpp
    src/grammars/function_syntax_node.cpp
    src/grammars/function_call_syntax_node.cpp
    src/grammars/while_expression_syntax_node.cpp
    src/grammars/varible_assigment_syntax_node.cpp
    src/grammars/conditional_expression_syntax_node.cpp
    src/grammars/scope_syntax_node.cpp
)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

add_subdirectory ("parser")
add_subdirectory ("tests/unit_tests")

target_include_directories(${PROJECT_NAME} PUBLIC "include" "include/grammars")
