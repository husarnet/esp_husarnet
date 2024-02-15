# System name used in multi-platform build system does not propagate from toolchain file in first script mode pass
set(CMAKE_SYSTEM_NAME Generic)

# Build husarnet component using internal CMake build system
include(${CMAKE_SOURCE_DIR}/husarnet/core/husarnet.cmake)
