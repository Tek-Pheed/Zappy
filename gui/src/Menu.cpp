/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Menu.cpp
*/

#include "Menu.hpp"
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <thread>
#include "Draw.hpp"
#include "Items.hpp"
#include "Map.hpp"
#include "RessourcePool.hpp"
#include "ServerData.hpp"
#include "Settings.hpp"
#include "Thread.hpp"

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
        screenWidth, screenHeight, "Zappy");
    return IsWindowReady();
}

void Zappy::Menu::LoadResources(RessourceManager &objectPool)
{
    Model &model = objectPool.models.dynamicLoad("korok", "assets/players/makar.obj");
    Music &MenuMusic =
        objectPool.musics.dynamicLoad("menu", "assets/musics/menu.mp3");
    Music &GameMusic =
        objectPool.musics.dynamicLoad("game", "assets/musics/game.mp3");
    Music &IncMusic =
        objectPool.musics.dynamicLoad("inc", "assets/musics/Zelda_Noïa_dance_song.mp3");
    Music &BroadMusic =
        objectPool.musics.dynamicLoad("broad", "assets/musics/Zelda_Korok_Yahaha.mp3");

    if (model.meshCount == 0) {
        std::cerr
            << "Erreur : Impossible de charger le modèle 'assets/players/makar.obj'"
            << std::endl;
        exit(1);
    }
    SetMusicVolume(MenuMusic, 0.5f);
    SetMusicVolume(GameMusic, 0.5f);
    SetMusicVolume(IncMusic, 1.0f);
    SetMusicVolume(BroadMusic, 1.0f);
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
    constexpr const char *models[] = {"assets/objects/food.obj",
        "assets/objects/rubis_korok.glb", "assets/objects/rubis_goron.glb",
        "assets/objects/rubis_zora.glb", "assets/objects/rubis_crepuscule.glb",
        "assets/objects/rubis_piaf.glb", "assets/objects/rubis_divin.glb"};

    for (std::size_t i = 0; i != Zappy::ITEM_MAX; i++)
        objectPool.models.loadRessource(Zappy::itemNames[i], models[i]);
}

std::list <BoundingBox> Zappy::Menu::setHitBox(std::list<Bloc *> bloc, RessourceManager &objectPool)
{
    std::list <Bloc *> tmp = bloc;
    std::list <BoundingBox> rectList;
    Model modelref = objectPool.models.dynamicLoad("water", "assets/water.obj");

    while(!tmp.empty()) {
        Vector3 posBase = {tmp.front()->getX() * 5.0f, 0.0f, tmp.front()->getY() * 5.0f};
        rectList.push_back(GetModelBoundingBox(modelref));
        Vector3 center = Vector3Scale(Vector3Add(rectList.back().min, rectList.back().max), 0.5f);
        Vector3 extents = Vector3Scale(Vector3Subtract(rectList.back().max, rectList.back().min), 0.5f * 0.5f);
        rectList.back().min = Vector3Subtract(center, extents);
        rectList.back().max = Vector3Add(center, extents);
        rectList.back().min = Vector3Add(rectList.back().min, posBase);
        rectList.back().max = Vector3Add(rectList.back().max, posBase);
        tmp.pop_front();
    }
    return rectList;
}

bool Zappy::Menu::CheckCollisionRayBox(Ray raycam, BoundingBox hitbox)
{
    float tminX = (hitbox.min.x - raycam.position.x) / raycam.direction.x;
    float tmaxX = (hitbox.max.x - raycam.position.x) / raycam.direction.x;
    float tminY = (hitbox.min.y - raycam.position.y) / raycam.direction.y;
    float tmaxY = (hitbox.max.y - raycam.position.y) / raycam.direction.y;
    float tminZ = (hitbox.min.z - raycam.position.z) / raycam.direction.z;
    float tmaxZ = (hitbox.max.z - raycam.position.z) / raycam.direction.z;

    if (tminX > tmaxX) std::swap(tminX, tmaxX);
    if (tminY > tmaxY) std::swap(tminY, tmaxY);
    if (tminZ > tmaxZ) std::swap(tminZ, tmaxZ);
    if ((tminX > tmaxY) || (tminY > tmaxX))
        return false;
    if (tminY > tminX)
        tminX = tminY;
    if (tmaxY < tmaxX)
        tmaxX = tmaxY;
    if ((tminX > tmaxZ) || (tminZ > tmaxX))
        return false;
    if (tminZ > tminX)
        tminX = tminZ;
    if (tmaxZ < tmaxX)
        tmaxX = tmaxZ;
    return true;
}

void Zappy::Menu::displayBlocinventory(Bloc *block)
{
    int food = block->countItem(items::food);
    int linemate = block->countItem(items::linemate);
    int deraumere = block->countItem(items::deraumere);
    int sibur = block->countItem(items::sibur);
    int mendiane = block->countItem(items::mendiane);
    int phiras = block->countItem(items::phiras);
    int thystame = block->countItem(items::thystame);
    DrawRectangle(0, GetScreenHeight() - 220, 200, 500, DARKGRAY);
    DrawText(TextFormat("Food: %d", food), 20, GetScreenHeight() - 200, 20, WHITE);
    DrawText(TextFormat("Linemate: %d", linemate), 20, GetScreenHeight() - 180, 20, WHITE);
    DrawText(TextFormat("Deraumere: %d", deraumere), 20, GetScreenHeight() - 160, 20, WHITE);
    DrawText(TextFormat("Sibur: %d", sibur), 20, GetScreenHeight() - 140, 20, WHITE);
    DrawText(TextFormat("Mendiane: %d", mendiane), 20, GetScreenHeight() - 120, 20, WHITE);
    DrawText(TextFormat("Phiras: %d", phiras), 20, GetScreenHeight() - 100, 20, WHITE);
    DrawText(TextFormat("Thystame: %d", thystame), 20, GetScreenHeight() - 80, 20, WHITE);
}

void Zappy::Menu::GameScene(RessourceManager &objectPool, Vector3 position,
    BoundingBox bounds, Zappy::Server server, Music music, Music incMusic, Music broadMusic)
{
    Zappy::Thread threadZappy;
    Zappy::Parser parser;
    bool isBroadMusicPlaying = false;

    std::string response;
    Players listPlayers;
    objectPool.models.loadRessource("water", "assets/environments/water.obj");
    objectPool.models.loadRessource("island", "assets/environments/island.obj");
    objectPool.models.loadRessource("player", "assets/players/makar.obj");

    Camera3D camera = {22.0f, 22.0f, 22.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        45.0f, CAMERA_PERSPECTIVE};

    std::list<Bloc *> blocks;
    std::list<Bloc *> tmpBlocks;
    Bloc *disInvBlock;
    loadItems(objectPool);

    (void) bounds;
    (void) position;

    PlayMusicStream(music);
    PlayMusicStream(incMusic);

    DisableCursor();
    SetTargetFPS(60);
    EnableCursor();
    // float velocityY = 0.0f;
    // const float gravity = -9.81f;
    // const float bounceFactor = 0.7f;
    // bool firstDrop = true;
    bool isBlocClicked = false;
    std::thread SPThread(&Zappy::Thread::ManageServer, &threadZappy,
        std::ref(server), std::ref(parser));
    bool cursorVisible = true;

    while (!WindowShouldClose()) {
        if (!cursorVisible) {
            UpdateCamera(&camera, CAMERA_FREE);
        }

        if (IsKeyPressed(KEY_C)) {
            cursorVisible = !cursorVisible;
            if (cursorVisible) {
                EnableCursor();
            } else {
                DisableCursor();
            }
        }
        blocks = parser.getMap().getBloc();
        tmpBlocks = blocks;
        std::list <BoundingBox> rectList = setHitBox(blocks, objectPool);
        listPlayers = parser.getPlayersList();
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            std::list <BoundingBox> rectListTmp = rectList;
            Ray ray = GetMouseRay(GetMousePosition(), camera);
            while (!rectListTmp.empty()) {
                if (CheckCollisionRayBox(ray, rectListTmp.front())){
                   isBlocClicked = true;
                   disInvBlock = tmpBlocks.front();
                }
                rectListTmp.pop_front();
                tmpBlocks.pop_front();
            }
        }
        if (parser.getInc())
            UpdateMusicStream(incMusic);
        else
            UpdateMusicStream(music);
        if (parser.getBroadcast() && !isBroadMusicPlaying) {
            PlayMusicStream(broadMusic);
            isBroadMusicPlaying = true;
            parser.setBroadcast(false);
        }
        if (isBroadMusicPlaying && IsMusicStreamPlaying(broadMusic))
            UpdateMusicStream(broadMusic);
        if (isBroadMusicPlaying && !IsMusicStreamPlaying(broadMusic))
            isBroadMusicPlaying = false;
        if (IsKeyPressed('Z'))
            camera.target = (Vector3){0.0f, 0.0f, 0.0f};
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        while (blocks.size() != 0) {
            blocks.front()->display(objectPool);
            blocks.pop_front();
        }
        for (const auto &variable : listPlayers.getPlayersList()) {
            variable.second->displayPlayer(objectPool);
        }
        EndMode3D();
        if (isBlocClicked) {
            displayBlocinventory(disInvBlock);
        }
        EndDrawing();
    }
    CloseWindow();
    threadZappy.setRunningFalse();
    SPThread.join();
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

    objectPool.textures.getRessource("background");
    Music &music = objectPool.musics.getRessource("menu");
    Music &GameMusic = objectPool.musics.getRessource("game");
    Music &IncMusic = objectPool.musics.getRessource("inc");
    Music &BroadMusic = objectPool.musics.getRessource("broad");
    Model &model = objectPool.models.getRessource("korok");

    PlayMusicStream(music);

    while (!WindowShouldClose()) {
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        int buttonWidth = screenWidth / 6;
        int buttonHeight = screenHeight / 10;
        int buttonHeightSettings = screenHeight / 7;
        int buttonXOffset = screenWidth / 2 - buttonWidth / 2;
        int playButtonYOffset = screenHeight / 2 - buttonHeightSettings / 2
            + buttonHeightSettings * 2;
        int settingsButtonYOffset = screenHeight / 2 + buttonHeightSettings / 2
            + buttonHeightSettings * 2;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        UpdateMusicStream(music);

        if (currentScene == Zappy::MENU) {
            DrawRectangle(0, 0, screenWidth, screenHeight, DARKGREEN);
            BeginMode3D(camera);
            DrawModel(model, position, 40.0f, WHITE);
            DrawBoundingBox(bounds, GREEN);
            EndMode3D();
            DrawText("MENU", screenWidth / 2 - MeasureText("MENU", 100) / 2,
                100, 100, LIGHTGRAY);

            playClicked = false;
            settingsClicked = false;

            draw.createButton(buttonWidth, buttonHeight, buttonXOffset,
                playButtonYOffset, 10, GREEN, BLACK, GREEN, "PLAY", 20, WHITE,
                Zappy::RECT, playClicked);
            if (playClicked == 1) {
                currentScene = Zappy::GAME;
            }
            draw.createButton(buttonWidth, buttonHeight, buttonXOffset,
                settingsButtonYOffset, 10, GREEN, BLACK, GREEN, "SETTINGS", 20,
                WHITE, Zappy::RECT, settingsClicked);
            if (settingsClicked == 1) {
                settingsIsClicked = !settingsIsClicked;
            }
            if (settingsIsClicked)
                s.manageSettingsButton(resIsClick, music, volume);
            else if (!settingsIsClicked)
                resIsClick = false;
        } else if (currentScene == Zappy::GAME) {
            server.init_connection(this->_host, std::stoi(this->_port));
            server.messConnect();
            music = GameMusic;
            GameScene(objectPool, position, bounds, server, music, IncMusic, BroadMusic);
        } else if (currentScene == Zappy::SETTINGS) {
            s.manageSettingsButton(resIsClick, music, volume);
            ClearBackground(RAYWHITE);
            DrawText("SETTINGS SCENE",
                screenWidth / 2 - MeasureText("SETTINGS SCENE", 40) / 2,
                screenHeight / 2 - 20, 40, DARKGRAY);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
}

void Zappy::Menu::UnloadResources(
    Model model, Texture2D texture_body, Texture2D texture_leaf)
{
    UnloadTexture(texture_body);
    UnloadTexture(texture_leaf);
    UnloadModel(model);
    CloseWindow();
}
