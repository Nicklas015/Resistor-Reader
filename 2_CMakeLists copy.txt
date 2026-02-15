cmake_minimum_required(VERSION 3.10)
project(color_reader)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(color_reader
    main.cpp
    color.cpp
    line.cpp
    cluster.cpp
    resistor_value.cpp
)

target_link_libraries(color_reader ${OpenCV_LIBS})
