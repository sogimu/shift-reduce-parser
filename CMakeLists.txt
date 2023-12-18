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
    include/grammars/e/sum/sum_syntax_node.h
    include/grammars/e/diff/diff_syntax_node.h
    include/grammars/e/e_syntax_node.h
    include/grammars/expression_syntax_node.h
    include/grammars/scope_syntax_node.h
    include/grammars/f_grammar.h
    include/grammars/e/sum/sum_grammar.h
    include/grammars/e/diff/diff_grammar.h
    include/grammars/e/e_grammar.h
    include/grammars/conditional_expression_syntax_node.h
    include/grammars/conditional_expression_grammar.h
    include/grammars/print_expression_syntax_node.h
    include/grammars/print_expression_grammar.h
    include/grammars/if_expression_syntax_node.h
    include/grammars/if_expression_grammar.h
    include/grammars/varible_assigment_syntax_node.h
    include/grammars/expression_grammar.h
    include/grammars/varible_assigment_grammar.h
    include/grammars/computational_expression_syntax_node.h
    include/grammars/computational_expression_grammar.h
    include/grammars/scope_grammar.h
#    include/grammars/f/t/mul/grammar.h
#    include/grammars/f/t/mul/syntax_node.h
#    include/grammars/f/t/div/grammar.h
#    include/grammars/f/t/div/syntax_node.h
#    include/grammars/f/t/grammar.h
#    include/grammars/f/t/syntax_node.h
#    include/grammars/p.h
#    include/grammars/assignment.h
#    include/grammars/expression.h
#    include/i_feature.h
#    include/features/many_of.h
)

set(SOURCES
    src/lexical_tokens.cpp
    src/grammars/base/plus_syntax_node.cpp
    src/grammars/base/minus_syntax_node.cpp
    src/grammars/base/bol_syntax_node.cpp
    src/grammars/base/eol_syntax_node.cpp
    src/grammars/base/number_syntax_node.cpp
    src/grammars/base/f_syntax_node.cpp
    src/grammars/base/semicolon_syntax_node.cpp
    src/grammars/base/print_syntax_node.cpp
    src/grammars/base/equal_syntax_node.cpp
    src/grammars/base/less_syntax_node.cpp
    src/grammars/base/more_syntax_node.cpp
    src/grammars/base/open_curly_bracket_syntax_node.cpp
    src/grammars/base/close_curly_bracket_syntax_node.cpp
    src/grammars/base/open_circle_bracket_syntax_node.cpp
    src/grammars/base/close_circle_bracket_syntax_node.cpp
    src/grammars/base/if_syntax_node.cpp
    src/grammars/base/name_syntax_node.cpp
    src/grammars/e_syntax_node.cpp
    src/grammars/sum_syntax_node.cpp
    src/grammars/diff_syntax_node.cpp
    src/grammars/computational_expression_syntax_node.cpp
    src/grammars/expression_syntax_node.cpp
    src/grammars/print_expression_syntax_node.cpp
    src/grammars/if_expression_syntax_node.cpp
    src/grammars/varible_assigment_syntax_node.cpp
    src/grammars/conditional_expression_syntax_node.cpp
    src/grammars/scope_syntax_node.cpp
#    src/grammars/f.cpp
#    src/grammars/t.cpp
#    src/grammars/p.cpp
    main.cpp
)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

add_subdirectory ("tests/unit_tests")

target_include_directories(${PROJECT_NAME} PUBLIC "include" "include/grammars")
