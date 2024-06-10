/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Menu.cpp
*/

#include <iostream>
#include "raylib.h"
#include "Menu.hpp"
#include "Draw.hpp"
#include "Settings.hpp"

Zappy::Scene currentScene = Zappy::MENU;

Zappy::Menu::Menu() {}
Zappy::Menu::~Menu() {}

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

void Zappy::Menu::ConfigureCamera(Camera &camera) {
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
    int playClicked = 0;
    int settingsClicked = 0;
    bool settingsIsClicked = 0;
    int exitClicked = 0;
    int confirmClicked = 0;
    Settings s;
    bool resIsClick = false;
    Music music;
    double volume = 0.5f;

    TextInput textInputPort(1350, 200, 320, 50);
    TextInput textInputIP(1350, 100, 320, 50);

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
            confirmClicked = false;

            draw.createButton(400, 75, 300, 700, 10, GREEN, BLACK, GREEN, "PLAY", 20, WHITE, Zappy::RECT, playClicked);
            if (playClicked == 1) {
                currentScene = Zappy::GAME;
            }
            draw.createButton(400, 75, 1220, 700, 10, GREEN, BLACK, GREEN, "SETTINGS", 20, WHITE, Zappy::RECT, settingsClicked);
            if (settingsClicked == 1) {
                settingsIsClicked = !settingsIsClicked;
            }
            if (settingsIsClicked)
                s.manageSettingsButton(resIsClick, music, volume);
            else if (!settingsIsClicked)
                resIsClick = false;
            draw.createButton(400, 75, 760, 900, 10, GREEN, BLACK, GREEN, "EXIT", 20, WHITE, Zappy::RECT, exitClicked);
            if (exitClicked == 1) {
                CloseWindow();
                break;
            }
            draw.createButton(400, 75, 760, 800, 10, GREEN, BLACK, GREEN, "CONFIRM", 20, WHITE, Zappy::RECT, confirmClicked);
            if (confirmClicked == 1) {
                std::string ip = textInputIP.GetText();
                std::string port = textInputPort.GetText();
                std::cout << "IP: " << ip << " Port: " << port << std::endl;
            }

            textInputPort.UpdateInput();
            textInputIP.UpdateInput();

            textInputPort.DrawInput();
            textInputIP.DrawInput();
        } else if (currentScene == Zappy::GAME) {
            GameScene(model, camera, position, bounds);
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
