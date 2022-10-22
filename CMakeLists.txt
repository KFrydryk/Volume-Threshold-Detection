cmake_minimum_required(VERSION 2.16)

# specify toolchain specific cmake stuff
set(CMAKE_TOOLCHAIN_FILE toolchains/Toolchain-arm-gcc.cmake)

project(Volume_Threshold)

add_subdirectory(src)

# specify compiler specific cmake stuff
include(toolchains/compiler-flags.cmake)

# specify platform specific cmake stuff
include(src/platform/stm32f407G/CMakeLists.txt)


# generate elf file
add_arm_executable(${CMAKE_PROJECT_NAME} src/main.c src/platform/stm32f407G/startup.c src/platform/stm32f407G/platform_init.c)
arm_link_libraries(${CMAKE_PROJECT_NAME} ${LIBRARIES} ${DRIVERS})