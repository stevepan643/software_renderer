add_library(stb STATIC
        stb_image.cpp
        stb_image_write.cpp
)

target_include_directories(stb
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)