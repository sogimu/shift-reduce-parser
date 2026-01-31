cmake_minimum_required(VERSION 3.6)
project(json_interpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включение поддержки CTest
enable_testing()

add_subdirectory ("project")
