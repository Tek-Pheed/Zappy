/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** main.cpp
*/

#include <iostream>
#include "raylib.h"
#include "../include/Draw.hpp"
#include <stdbool.h>

int main(void)
{
    Zappy::Draw draw;
    bool clicked = false;
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Texture2D background = LoadTexture("assets/background.png");

    Model model = LoadModel("assets/korok.glb");
    if (model.meshCount == 0) {
        std::cout << "Erreur : Impossible de charger le modèle 'assets/korok.glb'" << std::endl;
        return 1;
    }

    Texture2D texture_body = LoadTexture("assets/MakarBody.png");
    if (texture_body.id == 0) {
        std::cout << "Erreur : Impossible de charger la texture 'assets/MakarBody.png'" << std::endl;
        return 1;
    }
    Texture2D texture_leaf = LoadTexture("assets/MakarLeaf.png");
    if (texture_leaf.id == 0) {
        std::cout << "Erreur : Impossible de charger la texture 'assets/MakarLeaf.png'" << std::endl;
        return 1;
    }

    if (model.materialCount < 2) {

        model.materialCount = 2;
        model.materials = (Material *)realloc(model.materials, model.materialCount * sizeof(Material));
        model.materials[0] = LoadMaterialDefault();
        model.materials[1] = LoadMaterialDefault();
    }

    model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = texture_body;
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_leaf;

    for (int i = 0; i < model.meshCount; i++) {
        if (i == 0) {
            model.meshMaterial[i] = 0;
        } else {
            model.meshMaterial[i] = 1;
        }
    }

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 25.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 position = { 0.0f, 0.0f, 0.0f };
    BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        BeginMode3D(camera);
        DrawModel(model, position, 40.0f, WHITE);
        DrawBoundingBox(bounds, GREEN);
        EndMode3D();
        DrawText("ZAPPY", 775, 100, 100, LIGHTGRAY);
        // draw.createButton(200, 50, 700, 500, 10, BLUE, DARKBLUE, RED, "PLAY", 20, WHITE, Zappy::RECT, clicked);
        DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadTexture(texture_body);
    UnloadTexture(texture_leaf);
    UnloadModel(model);
    CloseWindow();

    return 0;
}
