set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Sti til Bootlin Toolchain
set(TOOLCHAIN_PATH $ENV{HOME}/armv6-eabihf--glibc--stable-2025.08-1)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/bin/arm-linux-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/arm-linux-g++)

# Din Raspberry Pi rootfs (kun til biblioteker)
set(PI_ROOTFS $ENV{HOME}/Resistor-Reader/rootfs)

# Brug Bootlin som primær sysroot for at sikre korrekte C++ headers
set(CMAKE_SYSROOT ${TOOLCHAIN_PATH}/arm-buildroot-linux-gnueabihf/sysroot)

# Flag til Raspberry Pi Zero
set(PI_ZERO_FLAGS "-mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp -marm")
set(CMAKE_C_FLAGS_INIT "${PI_ZERO_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "${PI_ZERO_FLAGS}")

# Søge-adfærd
set(CMAKE_FIND_ROOT_PATH ${PI_ROOTFS} ${CMAKE_SYSROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
