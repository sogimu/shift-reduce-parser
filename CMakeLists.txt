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
    include/grammars/terminals/bol_syntax_node.h
    include/grammars/terminals/eol_syntax_node.h
    include/grammars/terminals/plus_syntax_node.h
    include/grammars/terminals/minus_syntax_node.h
    include/grammars/terminals/asterisk_syntax_node.h
    include/grammars/terminals/slash_syntax_node.h
    include/grammars/terminals/number_syntax_node.h
    include/grammars/terminals/f_syntax_node.h
    include/grammars/terminals/semicolon_syntax_node.h
    include/grammars/terminals/print_syntax_node.h
    include/grammars/terminals/equal_syntax_node.h
    include/grammars/terminals/less_syntax_node.h
    include/grammars/terminals/more_syntax_node.h
    include/grammars/terminals/open_curly_bracket_syntax_node.h
    include/grammars/terminals/close_curly_bracket_syntax_node.h
    include/grammars/terminals/open_circle_bracket_syntax_node.h
    include/grammars/terminals/close_circle_bracket_syntax_node.h
    include/grammars/terminals/if_syntax_node.h
    include/grammars/terminals/name_syntax_node.h
    include/grammars/terminals/comma_syntax_node.h
    include/grammars/nonterminals/addition/addition_syntax_node.h
    include/grammars/nonterminals/subtraction/subtraction_syntax_node.h
    include/grammars/nonterminals/division/division_syntax_node.h
    include/grammars/nonterminals/expression_syntax_node.h
    include/grammars/nonterminals/scope_syntax_node.h
    include/grammars/nonterminals/conditional_expression_syntax_node.h
    include/grammars/nonterminals/print_expression_syntax_node.h
    include/grammars/nonterminals/if_expression_syntax_node.h
    include/grammars/nonterminals/function_syntax_node.h
    include/grammars/nonterminals/function_call_syntax_node.h
    include/grammars/nonterminals/while_expression_syntax_node.h
    include/grammars/nonterminals/varible_assigment_syntax_node.h
    include/grammars/nonterminals/computational_expression_syntax_node.h
    include/grammars/f_grammar.h
    include/grammars/conditional_expression_grammar.h
    include/grammars/print_expression_grammar.h
    include/grammars/if_expression_grammar.h
    include/grammars/while_expression_grammar.h
    include/grammars/expression_grammar.h
    include/grammars/varible_assigment_grammar.h
    include/grammars/computational_expression_grammar.h
    include/grammars/scope_grammar.h
    include/grammars/function_grammar.h
    include/grammars/function_call_grammar.h
)

set(SOURCES
    src/lexical_tokens.cpp
    src/grammars/terminals/plus_syntax_node.cpp
    src/grammars/terminals/minus_syntax_node.cpp
    src/grammars/terminals/asterisk_syntax_node.cpp
    src/grammars/terminals/slash_syntax_node.cpp
    src/grammars/terminals/bol_syntax_node.cpp
    src/grammars/terminals/eol_syntax_node.cpp
    src/grammars/terminals/number_syntax_node.cpp
    src/grammars/terminals/f_syntax_node.cpp
    src/grammars/terminals/semicolon_syntax_node.cpp
    src/grammars/terminals/comma_syntax_node.cpp
    src/grammars/terminals/print_syntax_node.cpp
    src/grammars/terminals/equal_syntax_node.cpp
    src/grammars/terminals/less_syntax_node.cpp
    src/grammars/terminals/more_syntax_node.cpp
    src/grammars/terminals/open_curly_bracket_syntax_node.cpp
    src/grammars/terminals/close_curly_bracket_syntax_node.cpp
    src/grammars/terminals/open_circle_bracket_syntax_node.cpp
    src/grammars/terminals/close_circle_bracket_syntax_node.cpp
    src/grammars/terminals/if_syntax_node.cpp
    src/grammars/terminals/while_syntax_node.cpp
    src/grammars/terminals/while_syntax_node.cpp
    src/grammars/terminals/name_syntax_node.cpp
    src/grammars/nonterminals/addition/addition_syntax_node.cpp
    src/grammars/nonterminals/subtraction/subtraction_syntax_node.cpp
    src/grammars/nonterminals/multiply/multiply_syntax_node.cpp
    src/grammars/nonterminals/division/division_syntax_node.cpp
    src/grammars/nonterminals/computational_expression_syntax_node.cpp
    src/grammars/nonterminals/expression_syntax_node.cpp
    src/grammars/nonterminals/print_expression_syntax_node.cpp
    src/grammars/nonterminals/if_expression_syntax_node.cpp
    src/grammars/nonterminals/function_syntax_node.cpp
    src/grammars/nonterminals/function_call_syntax_node.cpp
    src/grammars/nonterminals/while_expression_syntax_node.cpp
    src/grammars/nonterminals/varible_assigment_syntax_node.cpp
    src/grammars/nonterminals/conditional_expression_syntax_node.cpp
    src/grammars/nonterminals/scope_syntax_node.cpp
)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

add_subdirectory ("parser")
add_subdirectory ("tests/unit_tests")

target_include_directories(${PROJECT_NAME} PUBLIC "include" "include/grammars")
