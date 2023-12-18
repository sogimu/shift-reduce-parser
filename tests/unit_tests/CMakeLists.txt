cmake_minimum_required(VERSION 3.0)
project(unit_tests VERSION 0.0.1 LANGUAGES CXX)

add_executable(unit_tests
    syntax_tree_test.cpp
    dfs_pre_order_range_test.cpp
    create_syntax_node_tree_test.cpp
    main.cpp
)
target_link_libraries(unit_tests shift-reduce-parser)
target_include_directories(unit_tests PUBLIC "libs/doctest/include")
target_compile_features(unit_tests PRIVATE cxx_std_20)
