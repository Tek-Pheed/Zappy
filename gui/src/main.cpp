/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** main.cpp
*/

#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

int main(void)
{
    const int screenWidth = 2000;
    const int screenHeight = 1200;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Model model = LoadModel("assets/korok.obj");
    if (model.meshCount == 0) {
        std::cout << "Erreur : Impossible de charger le modèle 'assets/korok.obj" << std::endl;
        return 1;
    }

    Texture2D texture_body = LoadTexture("assets/MakarBody.png");
    if (texture_body.id == 0) {
        std::cout << "Erreur : Impossible de charger la texture 'assets/MakarBody.png" << std::endl;
        return 1;
    }
    Texture2D texture_leaf = LoadTexture("assets/MakarLeaf.png");
    if (texture_leaf.id == 0) {
        std::cout << "Erreur : Impossible de charger la texture 'assets/MakarLeaf.png" << std::endl;
        return 1;
    }

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_body;
    if (model.materialCount > 1) {
        model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = texture_leaf;
    } else {
        Material newMaterial = LoadMaterialDefault();
        model.materialCount++;
        model.materials = (Material *)realloc(model.materials, model.materialCount * sizeof(Material));
        model.materials[1] = newMaterial;
        model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = texture_leaf;
    }

    Camera camera = { 0 };
    camera.position = (Vector3){ 20.0f, 10.0f, 25.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 position = { 0.0f, 0.0f, 0.0f };
    BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);

    SetTargetFPS(600);

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        DrawModel(model, position, 60.0f, WHITE);
        EndMode3D();
        DrawText("ZAPPY LAND", 650, 100, 100, LIGHTGRAY);
        DrawFPS(10, 10);
        DrawGrid(20, 1.0f);
        EndDrawing();
    }
    UnloadTexture(texture_body);
    UnloadTexture(texture_leaf);
    UnloadModel(model);
    CloseWindow();
    return 0;
}
