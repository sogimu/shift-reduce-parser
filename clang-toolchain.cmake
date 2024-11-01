# Set the C and C++ compilers to Clang
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# Specify the C and C++ standard (optional)
set(CMAKE_C_STANDARD 11)  # Change to your desired C standard
set(CMAKE_CXX_STANDARD 20) # Change to your desired C++ standard

# Set additional compiler flags (optional)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2 -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2 -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11")

# Specify the sysroot if needed (optional)
# set(CMAKE_SYSROOT "/path/to/sysroot")

# Add any specific include directories or libraries if needed
# include_directories("/path/to/include")
# link_directories("/path/to/lib")

# Optionally define other variables like CMAKE_BUILD_TYPE
set(CMAKE_BUILD_TYPE "Debug")  # or "Debug", "RelWithDebInfo", etc.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

