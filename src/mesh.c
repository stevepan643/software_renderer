#include "mesh.h"

#include <stdlib.h>

#define TOBJ_ENABLE_FILE_IO
#include <stdio.h>

#include "pipeline.h"
#include "tiny_obj_c.h"

mesh_t *mesh_load_obj(const char *path) {
    mesh_t *mesh = malloc (sizeof(mesh_t));

    tobj_scene_f scene;
    tobj_load_config cfg = tobj_default_config();
    tobj_diag diag = {0};

    if (tobj_load_obj_from_file(&scene, path, &cfg, &diag) != TOBJ_OK)
    {
        fprintf(stderr, "Failed to load OBJ: %s\n", diag.err ? diag.err : "Unknown error");
        return NULL;
    }

    size_t total_indices = 0;
    for (size_t s = 0; s < scene.num_shapes; s++)
    {
        total_indices += scene.shapes[s].mesh.num_indices;
    }

    vertex_t *vertices = malloc(total_indices * sizeof(vertex_t));
    uint32_t *indices = malloc(total_indices * sizeof(uint32_t));
    size_t vertex_count = 0;

    for (size_t s = 0; s < scene.num_shapes; s++)
    {
        const tobj_mesh_f *mesh = &scene.shapes[s].mesh;

        for (size_t i = 0; i < mesh->num_indices; i++)
        {
            tobj_index idx = mesh->indices[i];
            vertex_t v = {0};

            // Position
            v.pos.x = scene.attrib.vertices.ptr[3 * idx.vertex_index + 0];
            v.pos.y = scene.attrib.vertices.ptr[3 * idx.vertex_index + 1];
            v.pos.z = scene.attrib.vertices.ptr[3 * idx.vertex_index + 2];

            // Normal
            if (scene.attrib.normals.ptr != NULL && idx.normal_index >= 0)
            {
                v.normal.x = scene.attrib.normals.ptr[3 * idx.normal_index + 0];
                v.normal.y = scene.attrib.normals.ptr[3 * idx.normal_index + 1];
                v.normal.z = scene.attrib.normals.ptr[3 * idx.normal_index + 2];
            }

            // UV Coordinates
            if (scene.attrib.texcoords.ptr != NULL && idx.texcoord_index >= 0)
            {
                v.uv.x = scene.attrib.texcoords.ptr[2 * idx.texcoord_index + 0];
                v.uv.y = scene.attrib.texcoords.ptr[2 * idx.texcoord_index + 1];
            }

            v.color = (vec3f_t){1.0f, 1.0f, 1.0f};

            vertices[vertex_count] = v;
            indices[vertex_count] = (uint32_t)vertex_count;
            vertex_count++;
        }
    }

    mesh->vertices = vertices;
    mesh->indices = indices;
    mesh->vertices_count = vertex_count;
    mesh->indices_count = total_indices;

    return mesh;
}
void mesh_free(mesh_t *mesh) {
    free(mesh->vertices);
    free(mesh->indices);
    free (mesh);
}