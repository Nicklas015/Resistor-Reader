cmake_minimum_required(VERSION 3.20)
project(ResistorReader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------
# Include & OpenCV Setup
# ------------------------------
include_directories(SYSTEM $ENV{HOME}/Resistor-Reader/rootfs/usr/include/opencv4)
set(OpenCV_DIR $ENV{HOME}/Resistor-Reader/rootfs/usr/lib/arm-linux-gnueabihf/cmake/opencv4)
find_package(OpenCV REQUIRED)

# ------------------------------
# Find math libs in sysroot
# ------------------------------
find_library(BLAS_LIB NAMES blas PATHS $ENV{HOME}/Resistor-Reader/rootfs/usr/lib/arm-linux-gnueabihf NO_DEFAULT_PATH)
find_library(LAPACK_LIB NAMES lapack PATHS $ENV{HOME}/Resistor-Reader/rootfs/usr/lib/arm-linux-gnueabihf NO_DEFAULT_PATH)
find_library(ARMADILLO_LIB NAMES armadillo PATHS $ENV{HOME}/Resistor-Reader/rootfs/usr/lib/arm-linux-gnueabihf NO_DEFAULT_PATH)
find_library(ARPACK_LIB NAMES arpack PATHS $ENV{HOME}/Resistor-Reader/rootfs/usr/lib/arm-linux-gnueabihf NO_DEFAULT_PATH)

# Optional: fail early if missing
if(NOT BLAS_LIB OR NOT LAPACK_LIB)
    message(FATAL_ERROR "BLAS/LAPACK not found in sysroot")
endif()

# ------------------------------
# Build Executable
# ------------------------------
add_executable(resistor-reader 
    main.cpp color.cpp line.cpp cluster.cpp resistor_value.cpp
)

target_link_options(resistor-reader PRIVATE
    "--sysroot=$ENV{HOME}/Resistor-Reader/rootfs"
    "-B$ENV{HOME}/Resistor-Reader/rootfs/usr/lib/arm-linux-gnueabihf"
    "-L$ENV{HOME}/Resistor-Reader/rootfs/usr/lib/arm-linux-gnueabihf"
    "-Wl,-rpath-link,$ENV{HOME}/Resistor-Reader/rootfs/usr/lib/arm-linux-gnueabihf"
    "-Wl,-rpath-link,$ENV{HOME}/Resistor-Reader/rootfs/lib/arm-linux-gnueabihf"
)

target_link_libraries(resistor-reader
    ${OpenCV_LIBS}
    ${ARMADILLO_LIB}
    ${ARPACK_LIB}
    ${BLAS_LIB}
    ${LAPACK_LIB}
    m
    pthread
    dl
)
