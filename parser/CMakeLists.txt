cmake_minimum_required(VERSION 3.0)
project(parser VERSION 0.0.1 LANGUAGES CXX)

# add_subdirectory(libs/Catch2)
# add_subdirectory(libs/googletest)

add_executable(parser
    src/main.cpp
)
# target_link_libraries(unit_tests PRIVATE shift-reduce-parser Catch2::Catch2)
target_link_libraries(parser PRIVATE shift-reduce-parser)
target_include_directories(parser PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(parser PRIVATE cxx_std_20)
