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

bool InitWindowAndResources(int screenWidth, int screenHeight) {
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    return IsWindowReady();
}

void LoadResources(Model &model, Texture2D &texture_body, Texture2D &texture_leaf) {
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

void ConfigureCamera(Camera &camera) {
    camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 25.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}


void TextBoxForPort(Rectangle textBox, bool mouseOnText, char port[MAX_INPUT_CHARS + 1], int letterCount, int framesCounter)
{
    if (mouseOnText) {
        framesCounter++;
    } else {
        framesCounter = 0;
    }

    BeginDrawing();
        DrawText("Entry port", 1350, 140, 20, GRAY);
        DrawRectangleRec(textBox, LIGHTGRAY);
        if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
        else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
        DrawText(port, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

        if (mouseOnText) {
            if (letterCount < MAX_INPUT_CHARS) {
                if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(port, 40), (int)textBox.y + 12, 40, MAROON);
            } else {
                DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
            }
        }
    EndDrawing();
}


void GameScene(Model model, Camera camera, Vector3 position, BoundingBox bounds) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);
    DrawBoundingBox(bounds, GREEN);
    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
}

void LoopForTextbox(Rectangle textBox, bool &mouseOnText, char name[MAX_INPUT_CHARS + 1], int &letterCount, int &framesCounter)
{
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
    else mouseOnText = false;

    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
                name[letterCount] = (char)key;
                name[letterCount + 1] = '\0';
                letterCount++;
            }
            key = GetCharPressed();
        }

        if (IsKeyDown(KEY_BACKSPACE)) {
            framesCounter++;
            if (framesCounter % 10 == 0) {  // Adjust the delay to your needs
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        } else {
            framesCounter = 0;
        }
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    TextBoxForPort(textBox, mouseOnText, name, letterCount, framesCounter);
}

void MainLoop(Model model, Texture2D background, Camera camera, Vector3 position, BoundingBox bounds, Zappy::Draw &draw)
{
    SetTargetFPS(60);
    bool playClicked = false;
    bool settingsClicked = false;
    bool exitClicked = false;
    char port[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;
    Rectangle textBox = { 1350, 200, 225, 50 };
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


void UnloadResources(Model model, Texture2D texture_body, Texture2D texture_leaf)
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
    Texture2D texture_body, texture_leaf;

    if (!InitWindowAndResources(screenWidth, screenHeight)) {
        std::cerr << "Erreur : Impossible d'initialiser la fenêtre et les ressources." << std::endl;
        return 1;
    }

    LoadResources(model, texture_body, texture_leaf);

    Camera camera;
    ConfigureCamera(camera);

    Vector3 position = { 0.0f, 0.0f, 0.0f };
    BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);

    Texture2D background = LoadTexture("assets/background.png");

    MainLoop(model, background, camera, position, bounds, draw);

    UnloadResources(model, texture_body, texture_leaf);

    return 0;
}
