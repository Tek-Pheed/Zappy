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

std::list <BoundingBox> Zappy::Menu::displayInventory(std::list<Bloc *> bloc)
{

    Vector2 mousePoint = GetMousePosition();
    std::list <Bloc *> tmp = bloc;
    std::list <BoundingBox> rectList;
    bool isHovered = false;
    int i = 0;
    std::cout << "bonjour je rentre dans displayInventory" << std::endl;
    while(!tmp.empty()) {
        rectList.push_front({{(float)tmp.front()->getX(), 0.0f, (float)tmp.front()->getY()},
                            {(float)tmp.front()->getX(), 0.0f, (float)tmp.front()->getY()}});
        tmp.pop_front();
    }
    return rectList;
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
    std::thread SPThread(&Zappy::Thread::ManageServer, &threadZappy,
        std::ref(server), std::ref(parser));
    bool cursorVisible = true;
    std::list <BoundingBox> rectList = displayInventory(parser.getMap().getBloc());

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
        listPlayers = parser.getPlayersList();
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            std::list <BoundingBox> rectListTmp = rectList;
            Ray ray = GetMouseRay(GetMousePosition(), camera);
            while (!rectListTmp.empty()) {
                if (CheckCollisionRayBox(ray, rectListTmp.front()))
                   std::cout << "hitbox est cliqué" << std::endl;
                rectListTmp.pop_front();
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
        std::list <BoundingBox> rectTmp = rectList;
        while (!rectTmp.empty()) {
            DrawBoundingBox(rectTmp.front(), RED);
            rectTmp.pop_front();
        }
        EndMode3D();
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
