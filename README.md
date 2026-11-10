# software-renderer

A software rasterizer written in C,
built as a learning project for **GAMES101: Introduction to Computer Graphics**.

It does not use any graphics API such as OpenGL or Vulkan.
All rendering is done on the CPU, from vertex processing to pixel shading.

![Viking Room](imgs/img.png)

## About

This project follows the GAMES101 course and implements a software rendering pipeline from scratch. 
The goal is to understand how the graphics pipeline works at the lowest level:
how vertices are transformed, 
how triangles are rasterized, 
how textures are sampled, 
and how lighting is computed.

## Features

- CPU rasterization with a standard rendering pipeline
- Texture loading and sampling with mipmap support
- Blinn-Phong lighting (ambient, diffuse, specular)
- OBJ model loading via tinyobjloader
- Back-face culling and depth testing
- Window management with SDL3
- Modular structure: pipeline, mesh, math, and window are separated

[GAMES101: Introduction to Computer Graphics](https://sites.cs.ucsb.edu/~lingqi/teaching/games101.html) by Lingqi Yan