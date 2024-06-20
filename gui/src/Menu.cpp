/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Menu.cpp
*/

#include <iostream>
#include <thread>
#include <raylib.h>
#include <raymath.h>
#include "Menu.hpp"
#include "Draw.hpp"
#include "Settings.hpp"
#include "ServerData.hpp"
#include "Map.hpp"
#include "Thread.hpp"
#include "Items.hpp"
#include "RessourcePool.hpp"

Zappy::Scene currentScene = Zappy::MENU;

Zappy::Menu::Menu() {}
Zappy::Menu::~Menu() {}

bool Zappy::Menu::InitWindowAndResources(int screenWidth, int screenHeight)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    return IsWindowReady();
}

void Zappy::Menu::LoadResources(RessourceManager &objectPool)
{
    Model &model = objectPool.models.dynamicLoad("korok", "assets/korok.glb");
    Music &MenuMusic =
        objectPool.musics.dynamicLoad("menu", "assets/menu.mp3");
    Music &GameMusic =
        objectPool.musics.dynamicLoad("game", "assets/game.mp3");
    Texture2D &texture_body =
        objectPool.textures.dynamicLoad("makarbody", "assets/MakarBody.png");
    Texture2D &texture_leaf =
        objectPool.textures.dynamicLoad("makaleaf", "assets/MakarLeaf.png");

    if (model.meshCount == 0) {
        std::cerr
            << "Erreur : Impossible de charger le modèle 'assets/korok.glb'"
            << std::endl;
        exit(1);
    }
    SetMusicVolume(MenuMusic, 0.5f);
    SetMusicVolume(GameMusic, 0.5f);
    if (texture_body.id == 0) {
        std::cerr << "Erreur : Impossible de charger la texture "
                     "'assets/MakarBody.png'"
                  << std::endl;
        exit(1);
    }
    if (texture_leaf.id == 0) {
        std::cerr << "Erreur : Impossible de charger la texture "
                     "'assets/MakarLeaf.png'"
                  << std::endl;
        exit(1);
    }
    if (model.materialCount < 2) {
        model.materialCount = 2;
        model.materials = (Material *) realloc(
            model.materials, model.materialCount * sizeof(Material));
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
    camera.position = (Vector3){0.0f, 2.0f, 25.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void loadItems(RessourceManager &objectPool)
{
    constexpr const char *models[] = {"assets/rubis/rubis_yigas.glb",
        "assets/rubis/rubis_korok.glb", "assets/rubis/rubis_goron.glb",
        "assets/rubis/rubis_zora.glb", "assets/rubis/rubis_crepuscule.glb",
        "assets/rubis/rubis_piaf.glb", "assets/rubis/rubis_divin.glb"};

    for (std::size_t i = 0; i != Zappy::ITEM_MAX; i++)
        objectPool.models.loadRessource(Zappy::itemNames[i], models[i]);
}


void Zappy::Menu::GameScene(RessourceManager &objectPool, Vector3 position,
    BoundingBox bounds, Zappy::Server server, Music music)
{
    Zappy::Thread threadZappy;
    Zappy::Parser parser;
    std::string response;
    Players listPlayers;
    objectPool.models.loadRessource("water", "assets/water.obj");
    objectPool.models.loadRessource("island", "assets/island.obj");
    objectPool.models.loadRessource("player", "assets/korok.glb");

    Camera3D camera = {22.0f, 22.0f, 22.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 45.0f,
    CAMERA_PERSPECTIVE};

    std::list<Bloc *> blocks;
    loadItems(objectPool);

    (void) bounds;
    (void) position;

    PlayMusicStream(music);
    DisableCursor();
    SetTargetFPS(60);
    float velocityY = 0.0f;
    const float gravity = -9.81f;
    const float bounceFactor = 0.7f;
    bool firstDrop = true;
    std::thread SPThread(&Zappy::Thread::ManageServer, &threadZappy, std::ref(server), std::ref(parser), std::ref(objectPool));

    while (!WindowShouldClose()) {
        blocks = parser.getMap().getBloc();
        listPlayers = parser.getPlayersList();
        UpdateCamera(&camera, CAMERA_FREE);
        UpdateMusicStream(music);
        if (IsKeyPressed('Z'))
            camera.target = (Vector3){0.0f, 0.0f, 0.0f};
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        while (blocks.size() != 0) {
            blocks.front()->display(objectPool);
            blocks.pop_front();
        }
        EndMode3D();
        EndDrawing();
    }
    CloseWindow();
}

void Zappy::Menu::MainLoop(RessourceManager &objectPool, Camera camera, Vector3 position, BoundingBox bounds, Zappy::Draw &draw)
{
    Zappy::Server server;
    SetTargetFPS(60);
    int playClicked = 0;
    int settingsClicked = 0;
    bool settingsIsClicked = 0;
    Settings s;
    bool resIsClick = false;
    double volume = 0.5f;

    Texture2D &background = objectPool.textures.getRessource("background");
    Music &music = objectPool.musics.getRessource("menu");
    Music &GameMusic = objectPool.musics.getRessource("game");
    Model &model = objectPool.models.getRessource("korok");

    PlayMusicStream(music);

    while (!WindowShouldClose()) {
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        int buttonWidth = screenWidth / 6;
        int buttonHeight = screenHeight / 10;
        int buttonHeightSettings = screenHeight / 7;
        int buttonXOffset = screenWidth / 2 - buttonWidth / 2;
        int playButtonYOffset = screenHeight / 2 - buttonHeightSettings / 2 + buttonHeightSettings * 2;
        int settingsButtonYOffset = screenHeight / 2 + buttonHeightSettings / 2 + buttonHeightSettings * 2;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentScene == Zappy::MENU) {
            DrawRectangle(0, 0, screenWidth, screenHeight, DARKGREEN);
            BeginMode3D(camera);
            DrawModel(model, position, 40.0f, WHITE);
            DrawBoundingBox(bounds, GREEN);
            EndMode3D();
            DrawText("MENU", screenWidth / 2 - MeasureText("MENU", 100) / 2, 100, 100, LIGHTGRAY);

            playClicked = false;
            settingsClicked = false;

            draw.createButton(buttonWidth, buttonHeight, buttonXOffset, playButtonYOffset, 10, GREEN, BLACK, GREEN, "PLAY", 20, WHITE, Zappy::RECT, playClicked);
            if (playClicked == 1) {
                currentScene = Zappy::GAME;
            }
            draw.createButton(buttonWidth, buttonHeight, buttonXOffset, settingsButtonYOffset, 10, GREEN, BLACK, GREEN, "SETTINGS", 20, WHITE, Zappy::RECT, settingsClicked);
            if (settingsClicked == 1) {
                settingsIsClicked = !settingsIsClicked;
            }
            if (settingsIsClicked)
                s.manageSettingsButton(resIsClick, music, volume);
            else if (!settingsIsClicked)
                resIsClick = false;
        } else if (currentScene == Zappy::GAME) {
            server.init_connection(this->_host, std::stoi(this->_port));
            music = GameMusic;
            GameScene(objectPool, position, bounds, server, music);
        } else if (currentScene == Zappy::SETTINGS) {
            s.manageSettingsButton(resIsClick, music, volume);
            ClearBackground(RAYWHITE);
            DrawText("SETTINGS SCENE", screenWidth / 2 - MeasureText("SETTINGS SCENE", 40) / 2, screenHeight / 2 - 20, 40, DARKGRAY);
            DrawFPS(10, 10);
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
