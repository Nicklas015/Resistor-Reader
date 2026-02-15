# ----------------------------------------
# Raspberry Pi Zero (ARMv6 hard-float)
# ----------------------------------------

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Sysroot
set(CMAKE_SYSROOT $ENV{HOME}/Resistor-Reader/rootfs)
set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})

# Tell CMake where to search packages
set(CMAKE_PREFIX_PATH
    ${CMAKE_SYSROOT}/usr
    ${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf/cmake/opencv4
)

# Compilers
set(TOOLCHAIN_PATH $ENV{HOME}/armv6-eabihf--glibc--stable-2024.05-1)
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

# Force ARMv6 + ARM mode
# Ret denne linje i din toolchain fil:
set(PI_ZERO_FLAGS "-mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -marm")


set(CMAKE_C_FLAGS_INIT "${PI_ZERO_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "${PI_ZERO_FLAGS}")

# Search behavior
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
