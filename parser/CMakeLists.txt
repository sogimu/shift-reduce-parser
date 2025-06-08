cmake_minimum_required(VERSION 3.5)
project(parser VERSION 0.0.1 LANGUAGES CXX)

# Enable AddressSanitizer
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Enabling AddressSanitizer")
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()

add_executable(parser
    src/varible_store.h
    src/function_store.h
    src/calculator.h
    src/calculator.cpp
    src/main.cpp
)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
find_package(Readline REQUIRED)

target_include_directories(parser PRIVATE ${READLINE_INCLUDE_DIR})

message(STATUS ${READLINE_INCLUDE_DIR})
message(STATUS ${READLINE_LIBRARIES})

if (NOT READLINE_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find readline include directory")
endif()

if (NOT READLINE_LIBRARY)
    message(FATAL_ERROR "Could not find readline library")
endif()

message(STATUS "Found readline include dir: ${READLINE_INCLUDE_DIR}")
message(STATUS "Found readline library: ${READLINE_LIBRARY}")

target_link_libraries(parser PRIVATE shift-reduce-parser ${READLINE_LIBRARIES})
target_include_directories(parser PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(parser PRIVATE cxx_std_20)
