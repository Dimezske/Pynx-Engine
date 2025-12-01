#ifndef TERRAIN_RENDERER_HPP
#define TERRAIN_RENDERER_HPP

#include <vector>
#include <iostream>
#include "topology.hpp"
#include "raylib.h"
#include "raymath.h"

// Draw terrain mesh with shader
inline void DrawTerrainMesh(const std::vector<std::vector<float>> &heightMap, Camera &camera, Shader &shader) {
    BeginMode3D(camera);
    BeginShaderMode(shader);

    for (int z = 0; z < gridSizeZ - 1; z++) {
        for (int x = 0; x < gridSizeX - 1; x++) {
            Vector3 v1 = {x * spacing, heightMap[z][x], z * spacing};
            Vector3 v2 = {(x + 1) * spacing, heightMap[z][x + 1], z * spacing};
            Vector3 v3 = {x * spacing, heightMap[z + 1][x], (z + 1) * spacing};
            Vector3 v4 = {(x + 1) * spacing, heightMap[z + 1][x + 1], (z + 1) * spacing};

            DrawLine3D(v1, v2, LIGHTGRAY);
            DrawLine3D(v1, v3, LIGHTGRAY);
            DrawLine3D(v2, v4, LIGHTGRAY);
            DrawLine3D(v3, v4, LIGHTGRAY);
        }
    }

    EndShaderMode();
    EndMode3D();
}

// Load terrain shader helper
inline Shader LoadTerrainShader(const char *vsFile, const char *fsFile) {
    Shader shader = LoadShader(vsFile, fsFile);
    if (shader.id == 0) std::cerr << "ERROR: Failed to load terrain shader!\n";
    return shader;
}

#endif // TERRAIN_RENDERER_HPP
