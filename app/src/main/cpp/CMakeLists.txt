cmake_minimum_required(VERSION 3.18.1)

set(libName native-opengles)

project(${libName})

file(GLOB source_file *.cpp
        ${CMAKE_SOURCE_DIR}/egl/*.cpp
        ${CMAKE_SOURCE_DIR}/looper/*.cpp
        ${CMAKE_SOURCE_DIR}/native-samples/*.cpp
        ${CMAKE_SOURCE_DIR}/render/*.cpp
        ${CMAKE_SOURCE_DIR}/util/*.cpp
        ${CMAKE_SOURCE_DIR}/platform/*.cpp
        ${CMAKE_SOURCE_DIR}/platform/ccUTF8.cpp
)

include_directories(
        ${CMAKE_SOURCE_DIR}/egl
        ${CMAKE_SOURCE_DIR}/glm
        ${CMAKE_SOURCE_DIR}/looper
        ${CMAKE_SOURCE_DIR}/native-samples
        ${CMAKE_SOURCE_DIR}/platform
        ${CMAKE_SOURCE_DIR}/render
        ${CMAKE_SOURCE_DIR}/util
        ${CMAKE_SOURCE_DIR}
)

add_library(
        ${libName}
        SHARED
        ${source_file}
)

find_library(
        log-lib
        log
)

target_link_libraries(
        ${libName}
        ${log-lib}
        android
        jnigraphics
        OpenSLES
        EGL
        GLESv3
)