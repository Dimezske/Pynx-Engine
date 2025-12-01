#ifndef CAMERA_MODULE_HPP
#define CAMERA_MODULE_HPP

#include "raylib.h"
#include "raygui.h"
#include "raymath.h"
#include <cmath>
#include <iostream>

// -------------------- Camera Settings --------------------
struct CameraSettings {
    // Movement
    float moveSpeed = 5.0f;
    float sprintMultiplier = 2.5f;
    float mouseSensitivity = 0.01f;

    // Orbit / fly
    bool orbitMode = false;
    float orbitDistance = 6.0f;

    // Smoothing
    float smoothSpeed = 8.0f;
    Vector3 smoothPosition = {0,0,0};
    Vector3 smoothTarget   = {0,0,0};
};

// -------------------- Initialization --------------------
inline void InitCamera(Camera &camera) {
    camera.position = {0.0f, 1.0f, 6.0f};
    camera.target   = {0.0f, 1.0f, 0.0f};
    camera.up       = {0.0f, 1.0f, 0.0f};
    camera.fovy     = 70.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

// -------------------- Helper Functions --------------------
inline Vector3 SmoothLerp(Vector3 current, Vector3 target, float speed, float dt) {
    return Vector3Add(current, Vector3Scale(Vector3Subtract(target, current), dt * speed));
}

// -------------------- Camera Update --------------------
inline void UpdateCamera(Camera &camera, CameraSettings &settings, float dt) {
    // Mouse rotation
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        Vector2 delta = GetMouseDelta();
        float rot_x = delta.x * settings.mouseSensitivity;
        float rot_y = delta.y * settings.mouseSensitivity;

        Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
        Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));

        if (settings.orbitMode) {
            camera.position = Vector3RotateByAxisAngle(camera.position, (Vector3){0,1,0}, -rot_x);
            forward = Vector3RotateByAxisAngle(forward, (Vector3){0,1,0}, -rot_x);

            camera.position = Vector3RotateByAxisAngle(camera.position, right, -rot_y);
            forward = Vector3RotateByAxisAngle(forward, right, -rot_y);

            camera.target = (Vector3){0,1,0};
        } else {
            camera.position = Vector3RotateByAxisAngle(camera.position, (Vector3){0,1,0}, -rot_x);
            forward = Vector3RotateByAxisAngle(forward, (Vector3){0,1,0}, -rot_x);

            camera.position = Vector3RotateByAxisAngle(camera.position, right, -rot_y);
            forward = Vector3RotateByAxisAngle(forward, right, -rot_y);

            camera.target = Vector3Add(camera.position, forward);
        }
    }

    // WASD fly movement
    Vector3 direction = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(direction, camera.up));
    float speed = settings.moveSpeed;
    if (IsKeyDown(KEY_LEFT_SHIFT)) speed *= settings.sprintMultiplier;

    Vector3 wishMove = {0};
    if (IsKeyDown(KEY_W)) wishMove = Vector3Add(wishMove, direction);
    if (IsKeyDown(KEY_S)) wishMove = Vector3Add(wishMove, Vector3Negate(direction));
    if (IsKeyDown(KEY_D)) wishMove = Vector3Add(wishMove, right);
    if (IsKeyDown(KEY_A)) wishMove = Vector3Add(wishMove, Vector3Negate(right));
    if (IsKeyDown(KEY_SPACE)) wishMove.y += 1;
    if (IsKeyDown(KEY_LEFT_CONTROL)) wishMove.y -= 1;

    if (!settings.orbitMode) {
        camera.position = Vector3Add(camera.position, Vector3Scale(wishMove, speed * dt));
        camera.target   = Vector3Add(camera.target, Vector3Scale(wishMove, speed * dt));
    }

    // Floor collision
    if (camera.position.y < 1.0f) {
        camera.position.y = 1.0f;
        camera.target.y   = 1.0f;
    }

    // Smoothing
    settings.smoothPosition = SmoothLerp(settings.smoothPosition, camera.position, settings.smoothSpeed, dt);
    settings.smoothTarget   = SmoothLerp(settings.smoothTarget, camera.target, settings.smoothSpeed, dt);

    camera.position = settings.smoothPosition;
    camera.target   = settings.smoothTarget;
}

// -------------------- UI --------------------
inline void DrawCameraUI(CameraSettings &settings, Camera &camera) {
    GuiPanel({10, 10, 300, 240}, "Camera Controls");

    GuiLabel({20, 40, 260, 20}, "Mouse Sensitivity");
    GuiSlider({20, 60, 260, 20}, nullptr, nullptr, &settings.mouseSensitivity, 0.001f, 0.05f);

    GuiLabel({20, 100, 260, 20}, "Movement Speed");
    GuiSlider({20, 120, 260, 20}, nullptr, nullptr, &settings.moveSpeed, 1.0f, 20.0f);

    GuiLabel({20, 160, 260, 20}, "Camera FOV");
    GuiSlider({20, 180, 260, 20}, nullptr, nullptr, &camera.fovy, 40.0f, 120.0f);

    GuiCheckBox({20, 215, 20, 20}, "Orbit Mode (TAB)", &settings.orbitMode);
}

// -------------------- Texture/Image Selector --------------------
inline void DrawCameraImageSelector() {
#ifndef NO_RAYGUI
    static int selectedImage = 0;
    const char comboText[] = "sand-1"; // only sand available

    GuiPanel({10, 400, 200, 150}, "Image Selector");
    selectedImage = GuiComboBox({20, 430, 160, 20}, comboText, &selectedImage);

    static Texture2D previewTexture = {0};
    static int lastSelected = -1;

    if (lastSelected != selectedImage) {
        if (previewTexture.id != 0) UnloadTexture(previewTexture);
        previewTexture = LoadTexture("textures/sand-1.png");
        lastSelected = selectedImage;
    }

    if (previewTexture.id != 0) {
        DrawTexturePro(previewTexture,
                       {0, 0, (float)previewTexture.width, (float)previewTexture.height},
                       {50, 480, 100, 100},
                       {0,0}, 0, WHITE);
    }
#endif
}

#endif // CAMERA_MODULE_HPP
