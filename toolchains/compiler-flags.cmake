# Compiler flags used for C and ASM files
set(CORE_FLAGS "-mcpu=cortex-m4 -mthumb -nostartfiles")

# Debug flag. Also dont use stdlib
set(DEBUG_FLAGS "${CORE_FLAGS} -g -O0 -nostartfiles")

# Hardware float support
set(CORE_FLAGS "${CORE_FLAGS} -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math")

# set cxx flags. Propably unnecessary, we don't plan to use cpp
set(CXX_FLAGS "-std=gnu++14 -O0 -g -fno-rtti -fno-exceptions -fverbose-asm -MMD")

# set cxx warnings. Propably unnecessary, we don't plan to use cpp
set(CXX_WARNINGS "-Wall -Wextra")

# Warnings
set(C_WARNINGS "-Wall -Wextra")

set(C_FLAGS "")

set(LD_SCRIPT ${CMAKE_SOURCE_DIR}/src/platform/stm32f407G/linker.ld)

# Linker flags
# -Wl, -Map - map file to be created
# -T - file with linker script
# -g - debug flag
# -Wl,--gc-sections - unused function removal
# set(LD_FLAGS "-Wl,-Map=${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.map,--cref -T ${LD_SCRIPT} -g -Wl,--gc-sections")
set(LD_FLAGS " -T ${LD_SCRIPT} -g")

set(CMAKE_CXX_FLAGS "${CORE_FLAGS} ${CXX_FLAGS} ${CXX_WARNINGS}")
set(CMAKE_C_FLAGS "${CORE_FLAGS} ${DEBUG_FLAGS} ${C_FLAGS} ${C_WARNINGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CORE_FLAGS} ${LD_FLAGS}")