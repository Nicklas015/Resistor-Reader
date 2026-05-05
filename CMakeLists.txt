cmake_minimum_required(VERSION 3.20)
project(ResistorReader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(SYSTEM 
    $ENV{HOME}/Resistor-Reader/rootfs/usr/include
    $ENV{HOME}/Resistor-Reader/rootfs/usr/include/opencv4
)

set(OpenCV_DIR $ENV{HOME}/Resistor-Reader/rootfs/usr/lib/arm-linux-gnueabihf/cmake/opencv4)
find_package(OpenCV REQUIRED)

set(GPIOD_LIB "$ENV{HOME}/Resistor-Reader/rootfs/usr/lib/arm-linux-gnueabihf/libgpiod.so.3.1.1")

add_executable(resistor-reader 
    main.cpp
    color.cpp
    line.cpp
    cluster.cpp
    resistor_value.cpp
    take_photo.cpp
    led_driver.cpp
)

target_link_options(resistor-reader PRIVATE
    "--sysroot=$ENV{HOME}/Resistor-Reader/rootfs"
    "-B$ENV{HOME}/Resistor-Reader/rootfs/usr/lib/arm-linux-gnueabihf"
    "-L$ENV{HOME}/Resistor-Reader/rootfs/usr/lib/arm-linux-gnueabihf"
    "-Wl,-rpath-link,$ENV{HOME}/Resistor-Reader/rootfs/usr/lib/arm-linux-gnueabihf"
    "-Wl,-rpath-link,$ENV{HOME}/Resistor-Reader/rootfs/lib/arm-linux-gnueabihf"
)

target_link_libraries(resistor-reader
    opencv_core
    opencv_imgcodecs
    opencv_imgproc
    ${GPIOD_LIB}
    pthread
)