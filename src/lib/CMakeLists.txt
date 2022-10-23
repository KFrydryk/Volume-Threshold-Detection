include("${PROJECT_SOURCE_DIR}/toolchains/compiler-flags.cmake")

set(INCLUDE_DIRS "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/src/lib/include" "${PROJECT_SOURCE_DIR}/src/platform/common/include")

add_library(testl test-lib.c)
target_include_directories(testl PUBLIC  ${INCLUDE_DIRS})

add_library(linked-list linked-list.c)
target_include_directories(linked-list PUBLIC  ${INCLUDE_DIRS})
