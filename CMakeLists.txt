cmake_minimum_required(VERSION 3.16)

project(sr LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET SDL3)

add_subdirectory(lib/stb)
add_subdirectory(lib/glm)

add_executable(sr
        src/main.cpp
        src/Window.cpp
        src/Window.h
)

set_target_properties(sr PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

target_include_directories(sr PRIVATE src)

target_link_libraries(sr PRIVATE
        PkgConfig::SDL3
        stb
        glm
)