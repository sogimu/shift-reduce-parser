cmake_minimum_required(VERSION 3.6)
project(parser LANGUAGES CXX)

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
    include/make_deep_syntax_node_copy.h
    include/make_shallow_syntax_node_copy.h
    include/syntax_node_state_machine_visitor.h
    include/is_last_nodes.h
    include/syntax_nodes/terminals/bol_syntax_node.h
    include/syntax_nodes/terminals/eol_syntax_node.h
    include/syntax_nodes/terminals/plus_syntax_node.h
    include/syntax_nodes/terminals/minus_syntax_node.h
    include/syntax_nodes/terminals/asterisk_syntax_node.h
    include/syntax_nodes/terminals/slash_syntax_node.h
    include/syntax_nodes/terminals/number_syntax_node.h
    include/syntax_nodes/terminals/f_syntax_node.h
    include/syntax_nodes/terminals/semicolon_syntax_node.h
    include/syntax_nodes/terminals/return_syntax_node.h
    include/syntax_nodes/terminals/print_syntax_node.h
    include/syntax_nodes/terminals/equal_syntax_node.h
    include/syntax_nodes/terminals/less_syntax_node.h
    include/syntax_nodes/terminals/more_syntax_node.h
    include/syntax_nodes/terminals/open_curly_bracket_syntax_node.h
    include/syntax_nodes/terminals/close_curly_bracket_syntax_node.h
    include/syntax_nodes/terminals/open_circle_bracket_syntax_node.h
    include/syntax_nodes/terminals/close_circle_bracket_syntax_node.h
    include/syntax_nodes/terminals/if_syntax_node.h
    include/syntax_nodes/terminals/function_syntax_node.h
    include/syntax_nodes/terminals/name_syntax_node.h
    include/syntax_nodes/terminals/comma_syntax_node.h
    include/syntax_nodes/nonterminals/un_expr_syntax_node.h
    include/syntax_nodes/nonterminals/bin_expr_syntax_node.h
    include/syntax_nodes/nonterminals/statment_syntax_node.h
    include/syntax_nodes/nonterminals/scope_statment_syntax_node.h
    include/syntax_nodes/nonterminals/print_statment_syntax_node.h
    include/syntax_nodes/nonterminals/if_statment_syntax_node.h
    include/syntax_nodes/nonterminals/function_statment_syntax_node.h
    include/syntax_nodes/nonterminals/function_call_syntax_node.h
    include/syntax_nodes/nonterminals/while_statment_syntax_node.h
    include/syntax_nodes/nonterminals/varible_assigment_statment_syntax_node.h
    include/syntax_nodes/nonterminals/varible_syntax_node.h
    include/syntax_nodes/nonterminals/return_statment_syntax_node.h
    include/grammars/f_grammar.h
    include/grammars/un_expr_grammar.h
    include/grammars/print_statment_grammar.h
    include/grammars/if_statment_grammar.h
    include/grammars/while_statment_grammar.h
    include/grammars/statment_grammar.h
    include/grammars/varible_assigment_grammar.h
    include/grammars/circle_brackets_grammar.h
    include/grammars/scope_grammar.h
    include/grammars/function_statment_grammar.h
    include/grammars/function_call_grammar.h
    include/grammars/return_statment_grammar.h
)

set(SOURCES
    src/lexical_tokens.cpp
    src/syntax_tree.cpp
    src/syntax_nodes/terminals/plus_syntax_node.cpp
    src/syntax_nodes/terminals/minus_syntax_node.cpp
    src/syntax_nodes/terminals/asterisk_syntax_node.cpp
    src/syntax_nodes/terminals/slash_syntax_node.cpp
    src/syntax_nodes/terminals/bol_syntax_node.cpp
    src/syntax_nodes/terminals/eol_syntax_node.cpp
    src/syntax_nodes/terminals/number_syntax_node.cpp
    src/syntax_nodes/terminals/f_syntax_node.cpp
    src/syntax_nodes/terminals/semicolon_syntax_node.cpp
    src/syntax_nodes/terminals/return_syntax_node.cpp
    src/syntax_nodes/terminals/comma_syntax_node.cpp
    src/syntax_nodes/terminals/print_syntax_node.cpp
    src/syntax_nodes/terminals/equal_syntax_node.cpp
    src/syntax_nodes/terminals/less_syntax_node.cpp
    src/syntax_nodes/terminals/more_syntax_node.cpp
    src/syntax_nodes/terminals/open_curly_bracket_syntax_node.cpp
    src/syntax_nodes/terminals/close_curly_bracket_syntax_node.cpp
    src/syntax_nodes/terminals/open_circle_bracket_syntax_node.cpp
    src/syntax_nodes/terminals/close_circle_bracket_syntax_node.cpp
    src/syntax_nodes/terminals/if_syntax_node.cpp
    src/syntax_nodes/terminals/while_syntax_node.cpp
    src/syntax_nodes/terminals/while_syntax_node.cpp
    src/syntax_nodes/terminals/function_syntax_node.cpp
    src/syntax_nodes/terminals/name_syntax_node.cpp
    src/syntax_nodes/nonterminals/un_expr_syntax_node.cpp
    src/syntax_nodes/nonterminals/bin_expr_syntax_node.cpp
    src/syntax_nodes/nonterminals/varible_syntax_node.cpp
    src/syntax_nodes/nonterminals/statment_syntax_node.cpp
    src/syntax_nodes/nonterminals/print_statment_syntax_node.cpp
    src/syntax_nodes/nonterminals/if_statment_syntax_node.cpp
    src/syntax_nodes/nonterminals/function_statment_syntax_node.cpp
    src/syntax_nodes/nonterminals/function_call_syntax_node.cpp
    src/syntax_nodes/nonterminals/while_statment_syntax_node.cpp
    src/syntax_nodes/nonterminals/varible_assigment_statment_syntax_node.cpp
    src/syntax_nodes/nonterminals/scope_statment_syntax_node.cpp
    src/syntax_nodes/nonterminals/return_statment_syntax_node.cpp
    src/grammars/circle_brackets_grammar.cpp
)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
  "include" 
  "include/grammars" 
  "include/syntax_nodes"
)

add_subdirectory ("tests/unit_tests")
