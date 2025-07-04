cmake_minimum_required(VERSION 3.17)

SET(BUILD_TARGET LINUX CACHE BOOL "")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

IF(NOT ${BUILD_TARGET} STREQUAL "PICO")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
ENDIF()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
project(elapsed_time_project C CXX ASM)

IF(${BUILD_TARGET} STREQUAL "PICO")
    add_definitions(-DPICO)
    include(pico_sdk_import.cmake)
ENDIF()

add_subdirectory(./src)

# IF(elapsed_time_TESTS AND NOT(${BUILD_TARGET} STREQUAL "PICO"))
# enable_testing()
# add_subdirectory(./tests)
# ENDIF()
