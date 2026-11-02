# Resistor-Reader

A C++ application for reading resistor color bands from an image. The project currently has two CMake configurations with different targets and assumptions; see [Build configurations](#build-configurations) before building.

## Build configurations

### Root configuration (`CMakeLists.txt`)

The root configuration builds the `resistor-reader` executable from the image-processing sources and `led_driver.cpp`. It requires C++17, OpenCV, and libgpiod. It also explicitly searches for Armadillo, ARPACK, BLAS, and LAPACK libraries.

**Important:** this configuration currently contains machine-specific cross-build paths under `$HOME/Resistor-Reader/rootfs`, expects ARM hard-float libraries, and links a fixed `libgpiod.so.3.1.1` path. The matching rootfs must exist and contain compatible target headers and libraries. These assumptions do not describe a generic native build and need to be adapted for the build host and target before using the commands below.

On a host with a configured CMake toolchain and matching dependency rootfs:

```sh
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=toolchains/rpi-zero.cmake
cmake --build build --parallel
```

The included toolchain file targets 32-bit ARMv6 hard-float (Raspberry Pi Zero), not 64-bit AArch64. Use it only when that is the intended target and the referenced compiler/sysroot and dependency rootfs are available.

### Local configuration (`local_CMakeLists.txt`)

This is a separate, simpler OpenCV-only configuration. It builds `color_reader` and omits `led_driver.cpp`; it is not selected by the ordinary `cmake -S .` command, which uses the root `CMakeLists.txt`. To try this configuration, first provide a separate source directory containing this file named `CMakeLists.txt`, or otherwise explicitly arrange for CMake to use it. It may not provide the GPIO functionality of the root target.

## Dependencies

For the root configuration, the C++17 compiler, CMake 3.20 or newer, OpenCV development files, and libgpiod development files are required. The CMake file also searches for Armadillo, ARPACK, BLAS, and LAPACK in the configured rootfs. Ensure all dependencies are built for the same architecture and ABI as the target; host libraries cannot be linked into a cross-compiled executable.

## Running

After building the root target, run it on a compatible target device:

```sh
./build/resistor-reader
```

The LED driver opens `/dev/gpiochip4`; successful GPIO operation also depends on that device and the required permissions being available on the target.

## Color calculation helper

If `cpp_test/calculator.cpp` is present in your checkout, build and run it with:

```sh
mkdir -p cpp_test/build
g++ -std=c++17 -Wall -g cpp_test/calculator.cpp -o cpp_test/build/calculator
./cpp_test/build/calculator
```
