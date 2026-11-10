#ifndef RASTERIZATION_MESH_H
#define RASTERIZATION_MESH_H
#include <stddef.h>
#include <stdint.h>

#include "vec.h"

typedef struct
{
    vec3f_t pos;
    vec3f_t normal;
    vec3f_t color;
    vec2f_t uv;
} vertex_t;

typedef struct
{
    vertex_t *vertices;
    uint32_t *indices;
    size_t vertices_count;
    size_t indices_count;
} mesh_t;

mesh_t *mesh_load_obj(const char *path);
void mesh_free(mesh_t *mesh);

#endif //RASTERIZATION_MESH_H
