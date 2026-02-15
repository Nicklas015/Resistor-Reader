# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(cmake_hello_world_test)

# Enable verbose output during the build process
# This is useful for debugging build issues
set(CMAKE_VERBOSE_MAKEFILE ON)

# Set the C++ standard to C++17
# This ensures that C++17 features are available for the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the executable target
# This creates an executable named 'cmake_hello_world_test' from the 'main.cpp' source file
add_executable(cmake_hello_world_test main.cpp)

# Optional: Add include directories if needed
# include_directories(include)

# Optional: Link libraries if needed
# target_link_libraries(cmake_hello_world_test some_library)

# Optional: Set compile options if needed
# target_compile_options(cmake_hello_world_test PRIVATE -Wall -Wextra)