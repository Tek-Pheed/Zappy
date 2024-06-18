/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Menu.cpp
*/

#include "Menu.hpp"
#include <iostream>
#include "Draw.hpp"
#include "Map.hpp"
#include "RessourcePool.hpp"
#include "ServerData.hpp"
#include "Settings.hpp"
#include "raylib.h"
#include "raymath.h"

Zappy::Scene currentScene = Zappy::MENU;

Zappy::Menu::Menu()
{
}
Zappy::Menu::~Menu()
{
}

bool Zappy::Menu::InitWindowAndResources(int screenWidth, int screenHeight)
{
    InitAudioDevice();
    InitWindow(
        screenWidth, screenHeight, "raylib [core] example - basic window");
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
    camera = {0};
    camera.position = (Vector3){0.0f, 2.0f, 25.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void Zappy::Menu::GameScene(RessourceManager &objectPool, Vector3 position,
    BoundingBox bounds, Zappy::Server server, Music music)
{
    Model water = objectPool.models.dynamicLoad("water", "assets/water.obj");
    Model island =
        objectPool.models.dynamicLoad("island", "assets/island.obj");
    Model food =
        objectPool.models.dynamicLoad("food", "assets/rubis/rubis_yigas.glb");
    Model linemate = objectPool.models.dynamicLoad(
        "linemate", "assets/rubis/rubis_korok.glb");
    Model deraumere = objectPool.models.dynamicLoad(
        "deraumere", "assets/rubis/rubis_goron.glb");
    Model sibur =
        objectPool.models.dynamicLoad("sibur", "assets/rubis/rubis_zora.glb");
    Model mendiane = objectPool.models.dynamicLoad(
        "mendiane", "assets/rubis/rubis_crepuscule.glb");
    Model phiras =
        objectPool.models.dynamicLoad("phiras", "assets/rubis/rubis_piaf.glb");
    Model thystame = objectPool.models.dynamicLoad(
        "thystame", "assets/rubis/rubis_divin.glb");
    Model player = objectPool.models.dynamicLoad("player", "assets/korok.glb");
    Zappy::Parser parser;
    std::string response;
    Camera3D camera = {0};
    std::list<Bloc *> blocks;
    Vector3 cubePosition = {0.0f, 0.0f, 0.0f};
    float velocityY = 0.0f;
    const float gravity = -9.81f;
    const float bounceFactor = 0.7f;
    bool firstDrop = true;

    (void) bounds;
    (void) position;

    camera.position = (Vector3){22.0f, 22.0f, 22.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    PlayMusicStream(music);
    DisableCursor();
    SetTargetFPS(60);
    server.receiveMess();
    parser.parsing(objectPool, server.getData());
    while (!WindowShouldClose()) {
        blocks = parser.getMap().getBloc();
        UpdateCamera(&camera, CAMERA_FREE);
        UpdateMusicStream(music);
        if (IsKeyPressed('Z'))
            camera.target = (Vector3){0.0f, 0.0f, 0.0f};
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        for (int x = 0; x < parser.getMap().getX(); x++) {
            for (int z = 0; z < parser.getMap().getY(); z++) {
                DrawModel(
                    water, (Vector3){x * 5.0f, 0.0f, z * 5.0f}, 0.5f, WHITE);
                DrawModel(
                    island, (Vector3){x * 5.0f, 0.0f, z * 5.0f}, 0.5f, WHITE);
            }
        }
        while (blocks.size() != 0) {
            std::vector<Zappy::items> items = blocks.front()->getItems();
            int i = 0;
            while (items.size() != 0) {
                Vector3 pos = {blocks.front()->getX() * 5.0f,
                    1.0f + (0.75f * i), blocks.front()->getY() * 5.0f};

                i++;
                if (pos.y <= (1.2f - (items.size() / 10))) {
                    pos.y = (1.2f - (items.size() / 10));
                    velocityY = -velocityY * bounceFactor;

                    if (fabs(velocityY) < 0.1f) {
                        velocityY = 0.0f;
                    }
                }
                if (items.back() == Zappy::items::food)
                    DrawModel(food, pos, 1.0f, WHITE);
                if (items.back() == Zappy::items::linemate)
                    DrawModel(linemate, pos, 1.0f, WHITE);
                if (items.back() == Zappy::items::deraumere)
                    DrawModel(deraumere, pos, 1.0f, WHITE);
                if (items.back() == Zappy::items::sibur)
                    DrawModel(sibur, pos, 1.0f, WHITE);
                if (items.back() == Zappy::items::mendiane)
                    DrawModel(mendiane, pos, 1.0f, WHITE);
                if (items.back() == Zappy::items::phiras)
                    DrawModel(phiras, pos, 1.0f, WHITE);
                if (items.back() == Zappy::items::thystame)
                    DrawModel(thystame, pos, 1.0f, WHITE);
                items.pop_back();
            }
            blocks.pop_front();
        }
        EndMode3D();
        EndDrawing();
        firstDrop = false;
    }
    CloseWindow();
}

void Zappy::Menu::MainLoop(RessourceManager &objectPool, Camera camera,
    Vector3 position, BoundingBox bounds, Zappy::Draw &draw)
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

            draw.createButton(400, 75, 760, 900, 10, GREEN, BLACK, GREEN,
                "SETTINGS", 20, WHITE, Zappy::RECT, settingsClicked);
            if (settingsClicked == 1) {
                settingsIsClicked = !settingsIsClicked;
            }
            if (settingsIsClicked)
                s.manageSettingsButton(resIsClick, music, volume);
            else if (!settingsIsClicked)
                resIsClick = false;
            draw.createButton(400, 75, 760, 800, 10, GREEN, BLACK, GREEN,
                "PLAY", 20, WHITE, Zappy::RECT, playClicked);
            if (playClicked == 1) {
                std::string ip = textInputIP.GetText();
                std::string port = textInputPort.GetText();
                std::cout << "IP: " << ip << " Port: " << port << std::endl;
                if (!port.empty()) {
                    server.init_connection(ip, std::stoi(port));
                    if (server.getIsconnect()) {
                        std::cout << "Connected to server" << std::endl;
                        server.messConnect();
                        currentScene = Zappy::GAME;
                    } else {
                        std::cerr << "Error: Connection to server failed"
                                  << std::endl;
                    }
                }
            }
            textInputPort.UpdateInput();
            textInputIP.UpdateInput();
            textInputPort.DrawInput();
            textInputIP.DrawInput();
        } else if (currentScene == Zappy::GAME) {
            music = GameMusic;
            GameScene(objectPool, position, bounds, server, music);
        } else if (currentScene == Zappy::SETTINGS) {
            s.manageSettingsButton(resIsClick, music, volume);
            ClearBackground(RAYWHITE);
            DrawText("SETTINGS SCENE",
                GetScreenWidth() / 2 - MeasureText("SETTINGS SCENE", 40) / 2,
                GetScreenHeight() / 2 - 20, 40, DARKGRAY);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
}
