add_library(tobj STATIC
        tiny_obj_c.c
        tobj_tess.c
)

target_compile_definitions(tobj PRIVATE TOBJ_ENABLE_FILE_IO)

target_include_directories(tobj
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)