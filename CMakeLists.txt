cmake_minimum_required(VERSION 3.20)
project(ResistorReader)
# Tving arkitekturen til ARMv6 (Pi Zero)
add_compile_options(-mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -marm)
add_link_options(-mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -marm)


# Standarder
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tjek for toolchain fil
if(NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Please specify your toolchain file with -DCMAKE_TOOLCHAIN_FILE=toolchains/rpi-zero.cmake")
endif()

# ------------------------------
# Include directories
# ------------------------------
# Bemærk: Vi bruger CMAKE_SYSROOT som base for at ramme din Raspberry Pi rootfs
include_directories(
    ${CMAKE_SYSROOT}/usr/include
    ${CMAKE_SYSROOT}/usr/include/opencv4
)

# ------------------------------
# Source files
# ------------------------------
set(SOURCES
    main.cpp
    color.cpp
    line.cpp
    cluster.cpp
    resistor_value.cpp
)

# ------------------------------
# Find OpenCV
# ------------------------------
# Fortæller CMake præcis hvor OpenCV konfigurationen ligger i din sysroot
set(OpenCV_DIR ${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf/cmake/opencv4)
find_package(OpenCV REQUIRED)

# ------------------------------
# Find biblioteker i sysroot (BLAS, LAPACK, Armadillo)
# ------------------------------
# Vi bruger NO_DEFAULT_PATH for at sikre, at vi IKKE linker mod din PC's egne biblioteker
find_library(BLAS_LIB NAMES blas PATHS ${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf NO_DEFAULT_PATH)
find_library(LAPACK_LIB NAMES lapack PATHS ${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf NO_DEFAULT_PATH)
find_library(ARMADILLO_LIB NAMES armadillo PATHS ${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf NO_DEFAULT_PATH)
find_library(ARPACK_LIB NAMES arpack PATHS ${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf NO_DEFAULT_PATH)

# Sikkerhedstjek: Stop hvis bibliotekerne mangler i din rootfs
if(NOT BLAS_LIB OR NOT LAPACK_LIB OR NOT ARMADILLO_LIB)
    message(FATAL_ERROR "Kunne ikke finde BLAS, LAPACK eller Armadillo i sysroot!\n"
            "Tjek om de findes i: ${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf/\n"
            "Husk at der skal være en .so fil (f.eks. libblas.so)")
endif()

# ------------------------------
# Create executable
# ------------------------------
add_executable(resistor-reader ${SOURCES})

target_link_libraries(resistor-reader
    ${OpenCV_LIBS}
    ${ARMADILLO_LIB}
    ${ARPACK_LIB}      # Tilføjet
    ${BLAS_LIB}
    ${LAPACK_LIB}
    m
    pthread
    dl                 # Tilføjet (nødvendig for nogle BLAS versioner)
)

# Dette tvinger linkeren til at lede efter OpenCV's afhængigheder i din rootfs
set_target_properties(resistor-reader PROPERTIES 
    LINK_FLAGS "-Wl,-rpath-link,${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf"
)
