/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** main.cpp
*/

#include <iostream>
#include "raylib.h"
#include "../include/Menu.hpp"
#include "../include/Draw.hpp"

Zappy::Scene currentScene = Zappy::MENU;

Zappy::Menu::Menu(){}
Zappy::Menu::~Menu(){}

bool Zappy::Menu::InitWindowAndResources(int screenWidth, int screenHeight)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    return IsWindowReady();
}

void Zappy::Menu::LoadResources(Model &model, Texture2D &texture_body, Texture2D &texture_leaf)
{
    model = LoadModel("assets/korok.glb");
    if (model.meshCount == 0) {
        std::cerr << "Erreur : Impossible de charger le modèle 'assets/korok.glb'" << std::endl;
        exit(1);
    }

    texture_body = LoadTexture("assets/MakarBody.png");
    if (texture_body.id == 0) {
        std::cerr << "Erreur : Impossible de charger la texture 'assets/MakarBody.png'" << std::endl;
        exit(1);
    }

    texture_leaf = LoadTexture("assets/MakarLeaf.png");
    if (texture_leaf.id == 0) {
        std::cerr << "Erreur : Impossible de charger la texture 'assets/MakarLeaf.png'" << std::endl;
        exit(1);
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
        model.meshMaterial[i] = (i == 0) ? 0 : 1;
    }
}

void Zappy::Menu::ConfigureCamera(Camera &camera)
{
    camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 25.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void Zappy::Menu::GameScene(Model model, Camera camera, Vector3 position, BoundingBox bounds)
{
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);
    DrawBoundingBox(bounds, GREEN);
    EndMode3D();
    DrawFPS(10, 10);
}

void Zappy::Menu::MainLoop(Model model, Texture2D background, Camera camera, Vector3 position, BoundingBox bounds, Zappy::Draw &draw)
{
    SetTargetFPS(60);
    bool playClicked = false;
    bool settingsClicked = false;
    bool exitClicked = false;
    char port[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;
    Rectangle textBox = { 1350, 200, 320, 50 };
    bool mouseOnText = false;
    int framesCounter = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentScene == Zappy::MENU) {
            DrawTexture(background, 0, 0, WHITE);
            BeginMode3D(camera);
            DrawModel(model, position, 40.0f, WHITE);
            DrawBoundingBox(bounds, GREEN);
            EndMode3D();
            DrawText("MENU", 775, 100, 100, LIGHTGRAY);

            playClicked = false;
            settingsClicked = false;
            exitClicked = false;

            if (draw.createButton(400, 75, 300, 700, 10, GREEN, BLACK, GREEN, "PLAY", 20, WHITE, Zappy::RECT, playClicked)) {
                currentScene = Zappy::GAME;
            }
            if (draw.createButton(400, 75, 1220, 700, 10, GREEN, BLACK, GREEN, "SETTINGS", 20, WHITE, Zappy::RECT, settingsClicked)) {
                currentScene = Zappy::SETTINGS;
            }
            if (draw.createButton(400, 75, 760, 900, 10, GREEN, BLACK, GREEN, "EXIT", 20, WHITE, Zappy::RECT, exitClicked)) {
                CloseWindow();
                break;
            }
        } else if (currentScene == Zappy::GAME) {
            GameScene(model, camera, position, bounds);
        } else if (currentScene == Zappy::SETTINGS) {
            ClearBackground(RAYWHITE);
            DrawText("SETTINGS SCENE", GetScreenWidth() / 2 - MeasureText("SETTINGS SCENE", 40) / 2, GetScreenHeight() / 2 - 20, 40, DARKGRAY);
            DrawFPS(10, 10);
        }

        if (currentScene == Zappy::MENU) {
            LoopForTextbox(textBox, mouseOnText, port, letterCount, framesCounter);
        }

        EndDrawing();
    }
}

void Zappy::Menu::UnloadResources(Model model, Texture2D texture_body, Texture2D texture_leaf)
{
    UnloadTexture(texture_body);
    UnloadTexture(texture_leaf);
    UnloadModel(model);
    CloseWindow();
}

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    Model model;
    Zappy::Draw draw;
    Zappy::Menu menu;
    Texture2D texture_body, texture_leaf;

    if (!menu.InitWindowAndResources(screenWidth, screenHeight)) {
        std::cerr << "Erreur : Impossible d'initialiser la fenêtre et les ressources." << std::endl;
        return 1;
    }

    menu.LoadResources(model, texture_body, texture_leaf);

    Camera camera;
    menu.ConfigureCamera(camera);

    Vector3 position = { 0.0f, 0.0f, 0.0f };
    BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);

    Texture2D background = LoadTexture("assets/background.png");

    menu.MainLoop(model, background, camera, position, bounds, draw);

    menu.UnloadResources(model, texture_body, texture_leaf);

    return 0;
}
