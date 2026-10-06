cmake_minimum_required(VERSION 3.16)

project(Rasterization LANGUAGES C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET SDL3)

add_subdirectory(lib/stb)
add_subdirectory(lib/tinyobjloader)

add_executable(Rasterization
        src/main.c
        src/window.c
        src/pipeline.c
        src/texture.c
)

set_target_properties(Rasterization PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

target_include_directories(Rasterization PRIVATE src)

target_link_libraries(Rasterization PRIVATE
        PkgConfig::SDL3
        stb
        tobj
)
