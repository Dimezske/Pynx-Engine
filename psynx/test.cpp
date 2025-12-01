#include "raylib.h"
#include "raygui.h"
#include "raymath.h"

#include "camera_module.hpp"
#include "terrain_renderer.hpp"
#include "topology.hpp"

#include <iostream>
#include <vector>

struct CameraCollider {
    Vector3 position = {0, 0.5f, 0};
    float radius = 0.5f;
};

int main() {
    // ----------------- Window -----------------
    InitWindow(1280, 720, "Pysnx Engine 0.01-alpha");
    SetTargetFPS(60);

    // ----------------- Camera -----------------
    Camera camera = {0};
    InitCamera(camera);

    CameraSettings camSettings;
    camSettings.smoothPosition = camera.position;
    camSettings.smoothTarget   = camera.target;

    CameraCollider collider;

    bool showUI = true;

    // ----------------- Terrain -----------------
    std::vector<std::vector<float>> heightMap = GenerateHeightMap();

    Shader terrainShader = LoadTerrainShader("shaders/terrain.vs", "shaders/terrain.fs");
    if (terrainShader.id == 0) std::cerr << "ERROR: Failed to load terrain shader!\n";

    // ----------------- Main loop -----------------
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Toggle UI and orbit mode
        if (IsKeyPressed(KEY_F1)) showUI = !showUI;
        if (IsKeyPressed(KEY_TAB)) camSettings.orbitMode = !camSettings.orbitMode;

        // Update camera
        UpdateCamera(camera, camSettings, dt);

        // ----------------- Drawing -----------------
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Draw terrain mesh
        DrawTerrainMesh(heightMap, camera, terrainShader);

        // Draw test collider sphere
        DrawSphere(collider.position, collider.radius, GREEN);

        // Draw UI if enabled
        if (showUI) {
            DrawCameraUI(camSettings, camera);
            DrawCameraImageSelector();
        }

        // FPS counter
        DrawFPS(1180, 10);

        EndDrawing();
    }

    // ----------------- Cleanup -----------------
    UnloadShader(terrainShader);
    CloseWindow();
    return 0;
}
