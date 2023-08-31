cmake_minimum_required(VERSION 3.5)
project(calculator_simple LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    include/enums.h
    include/lexical_tokens.h
    include/syntax_tree.h
    include/utils.h
    include/i_grammar.h
    include/grammars/f.h
    include/grammars/e.h
    include/grammars/t.h
    include/grammars/p.h
    include/grammars/assignment.h
)

set(SOURCES
    src/lexical_tokens.cpp
    src/syntax_tree.cpp
    src/grammars/f.cpp
    src/grammars/e.cpp
    src/grammars/t.cpp
    src/grammars/p.cpp
    main.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "include" "include/grammars")
