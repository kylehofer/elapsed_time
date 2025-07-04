set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

SET(ELAPSED_TIME_STATIC ON CACHE BOOL "")

# Finding all of our source
file(GLOB_RECURSE SOURCES ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR} "./*.cpp")
file(GLOB_RECURSE HEADERS ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/*.h*")

IF(ELAPSED_TIME_STATIC)
    add_library(elapsed_time STATIC ${SOURCES} ${HEADERS})
ELSEIF(SHARED_LIBRARY)
    add_library(elapsed_time SHARED ${SOURCES} ${HEADERS})
ENDIF()

target_include_directories(elapsed_time PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")

IF(${BUILD_TARGET} STREQUAL "PICO")
    target_link_libraries(elapsed_time
        pico_stdlib
    )
ENDIF()
