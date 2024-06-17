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
    InitAudioDevice();
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    return IsWindowReady();
}

void Zappy::Menu::LoadResources(Model &model, Texture2D &texture_body, Texture2D &texture_leaf, Music &MenuMusic, Music &GameMusic)
{
    model = LoadModel("assets/korok.glb");
    if (model.meshCount == 0) {
        std::cerr << "Erreur : Impossible de charger le modèle 'assets/korok.glb'" << std::endl;
        exit(1);
    }

    MenuMusic = LoadMusicStream("assets/menu.mp3");
    SetMusicVolume(MenuMusic, 0.5f);

    GameMusic = LoadMusicStream("assets/game.mp3");
    SetMusicVolume(GameMusic, 0.5f);

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

void Zappy::Menu::GameScene(Model model, Vector3 position, BoundingBox bounds, Music music)
{
    Model water;
    Model heart;
    Model chest;
    Model tree;
    Model island;
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    water = LoadModel("assets/item/water.glb");
    heart = LoadModel("assets/item/heart.glb");
    chest = LoadModel("assets/item/chest_island.glb");
    tree = LoadModel("assets/item/palm_tree_island.glb");
    island = LoadModel("assets/item/basic_island.glb");
    PlayMusicStream(music);

    DisableCursor();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);
        UpdateMusicStream(music);

        if (IsKeyPressed('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                for (int x = 0; x < 20; x++) {
                    for (int z = 0; z < 20; z++) {
                        DrawModel(water, (Vector3){ x * 2.0f, 0.0f, z * 2.0f }, 1.0f, WHITE);
                    }
                }
                DrawModel(heart, (Vector3){ 0.0f, 2.0f, 0.0f }, 1.0f, WHITE);
                // DrawModel(chest, (Vector3){ 2.0f, 0.0f, 0.0f }, 1.0f, WHITE);
                DrawModel(tree, (Vector3){ 4.0f, 2.0f, 0.0f }, 1.0f, WHITE);
                DrawModel(island, (Vector3){ 0.0f, 2.0f, 0.0f }, 1.0f, WHITE);
                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawText("Free camera default controls:", 20, 20, 10, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
            DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}

void Zappy::Menu::MainLoop(Model model, Texture2D background, Camera camera, Vector3 position, BoundingBox bounds, Zappy::Draw &draw, Music &MenuMusic, Music &GameMusic)
{
    SetTargetFPS(60);
    int playClicked = 0;
    int settingsClicked = 0;
    bool settingsIsClicked = 0;
    int exitClicked = 0;
    int confirmClicked = 0;
    Settings s;
    bool resIsClick = false;
    double volume = 0.5f;
    Music music = MenuMusic;

    TextInput textInputPort(1350, 200, 320, 50);
    TextInput textInputIP(1350, 100, 320, 50);
    PlayMusicStream(music);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        UpdateMusicStream(music);

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
            music = GameMusic;
            GameScene(model, position, bounds, music);
        } else if (currentScene == Zappy::SETTINGS) {
            s.manageSettingsButton(resIsClick, music, volume);
            ClearBackground(RAYWHITE);
            DrawText("SETTINGS SCENE", GetScreenWidth() / 2 - MeasureText("SETTINGS SCENE", 40) / 2, GetScreenHeight() / 2 - 20, 40, DARKGRAY);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
}
void Zappy::Menu::UnloadResources(Model model, Texture2D texture_body, Texture2D texture_leaf, Music MenuMusic, Music GameMusic)
{
    UnloadTexture(texture_body);
    UnloadTexture(texture_leaf);
    UnloadModel(model);
    UnloadMusicStream(MenuMusic);
    UnloadMusicStream(GameMusic);
    CloseWindow();
}