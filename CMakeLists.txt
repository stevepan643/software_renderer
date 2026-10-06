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

set(SRCS
    src/main.c
    src/window.c
    src/pipeline.c
        lib/stb/stb_image_write.c
        lib/stb/stb_image.c
)

set(LIB_SRC
    src/stb_image_impl.c
    src/tiny_obj_c.c
    src/tobj_tess.c
    src/texture.c
)

add_executable(Rasterization ${SRCS})

set_target_properties(Rasterization PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

target_include_directories(Rasterization PRIVATE src)

target_link_libraries(Rasterization PRIVATE PkgConfig::SDL3)

target_compile_options(Rasterization PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Werror=implicit-function-declaration
    -Werror=return-type
    -Werror=incompatible-pointer-types
    -fno-common
)

add_library(thirdparty OBJECT ${LIB_SRC})

target_include_directories(thirdparty PRIVATE src)
target_compile_definitions(thirdparty PRIVATE TOBJ_ENABLE_FILE_IO)
target_compile_options(thirdparty PRIVATE -O2 -g)

target_sources(Rasterization PRIVATE $<TARGET_OBJECTS:thirdparty>)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(Rasterization PRIVATE
        -O0 -g3 -DDEBUG
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )
    target_link_options(Rasterization PRIVATE
        -fsanitize=address,undefined
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(Rasterization PRIVATE
        -O3 -march=native -funroll-loops
        -fno-math-errno -fno-trapping-math
        -DNDEBUG -D_FORTIFY_SOURCE=2
        -fstack-protector-strong
    )
endif()
