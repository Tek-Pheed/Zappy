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
#include <cmath>

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
    InitWindow(screenWidth, screenHeight, "Zappy");
    return IsWindowReady();
}

void Zappy::Menu::LoadResources(RessourceManager &objectPool)
{
    Model &model = objectPool.models.dynamicLoad("korok", "assets/players/makar.obj");
    Music &MenuMusic = objectPool.musics.dynamicLoad("menu", "assets/musics/menu.mp3");
    Music &GameMusic = objectPool.musics.dynamicLoad("game", "assets/musics/game.mp3");
    Music &IncMusic = objectPool.musics.dynamicLoad("inc", "assets/musics/Zelda_Noïa_dance_song.mp3");
    Music &BroadMusic = objectPool.musics.dynamicLoad("broad", "assets/musics/Zelda_Korok_Yahaha.mp3");

    if (model.meshCount == 0) {
        std::cerr << "Erreur : Impossible de charger le modèle 'assets/players/makar.obj'" << std::endl;
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
    constexpr const char *models[] = {
        "assets/objects/food.obj",
        "assets/objects/rubis_korok.glb", "assets/objects/rubis_goron.glb",
        "assets/objects/rubis_zora.glb", "assets/objects/rubis_crepuscule.glb",
        "assets/objects/rubis_piaf.glb", "assets/objects/rubis_divin.glb"
    };

    for (std::size_t i = 0; i != Zappy::ITEM_MAX; i++)
        objectPool.models.loadRessource(Zappy::itemNames[i], models[i]);
}

void Zappy::Menu::GameScene(RessourceManager &objectPool, Vector3 position,
    BoundingBox bounds, Zappy::Server server, Music music, Music incMusic, Music broadMusic)
{
    float cameraAngle = 0.0f;
    float cameraDistance = 50.0f;
    Zappy::Thread threadZappy;
    Zappy::Parser parser;
    bool isBroadMusicPlaying = false;
    std::map<int, int> listLvl;
    for (int i = 1; i <= 8; i++) {
        listLvl[i] = 0;
    }

    std::string response;
    Players listPlayers;
    objectPool.models.loadRessource("water", "assets/environments/water.obj");
    objectPool.models.loadRessource("island", "assets/environments/island.obj");
    objectPool.models.loadRessource("player", "assets/players/makar.obj");

    int mapX = 0;
    int mapY = 0;
    Vector3 mapCenter = {0.0f, 0.0f, 0.0f};

    Camera3D camera;
    camera.position = {0.0f, 0.0f, 0.0f}; // Initialisation explicite
    camera.target = {0.0f, 0.0f, 0.0f};   // Initialisation explicite
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    std::list<Bloc *> blocks;
    loadItems(objectPool);

    (void)bounds;
    (void)position;

    PlayMusicStream(music);
    PlayMusicStream(incMusic);

    DisableCursor();
    SetTargetFPS(60);

    std::thread SPThread(&Zappy::Thread::ManageServer, &threadZappy,
        std::ref(server), std::ref(parser));

    while (!WindowShouldClose()) {
        blocks = parser.getMap().getBloc();
        listPlayers = parser.getPlayersList();

        if (IsKeyDown(KEY_RIGHT)) {
            cameraAngle += GetFrameTime();
        }
        if (IsKeyDown(KEY_LEFT)) {
            cameraAngle -= GetFrameTime();
        }

        camera.position.x = mapCenter.x + cameraDistance * cos(cameraAngle);
        camera.position.z = mapCenter.z + cameraDistance * sin(cameraAngle);

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
            camera.target = mapCenter;
        BeginDrawing();
            mapX = parser.getMap().getX();
            mapY = parser.getMap().getY();
            mapCenter = {(mapX / 2.0f) * 5 - 2.5f, 0.0f, (mapY / 2.0f) * 5 - 2.5f};
            camera.position = (Vector3){mapCenter.x + cameraDistance * cos(cameraAngle), 30.0f, mapCenter.z + cameraDistance * sin(cameraAngle)};
            camera.target = mapCenter;
        ClearBackground(RAYWHITE);
        DrawLevels(parser, listLvl);
        BeginMode3D(camera);
        while (blocks.size() != 0) {
            blocks.front()->display(objectPool);
            blocks.pop_front();
        }
        for (const auto &variable : listPlayers.getPlayersList()) {
            if (variable.second != nullptr)
                variable.second->displayPlayer(objectPool);
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

void Zappy::Menu::DrawLevels(Zappy::Parser &parser, std::map<int, int> listLvl)
{
    std::map<int, Player*> playerListTmp = parser.getPlayersList().getPlayersList();
    int y = 45;

    for (const auto &variable : playerListTmp) {
        if (variable.second != nullptr)
            listLvl[variable.second->getLvl()] += 1;
    }

    DrawRectangle(15, 15, 240, 330, BLACK);
    DrawRectangle(20, 20, 230, 320, GRAY);
    DrawText("LVL 1 :", 40, 45, 30, BLACK);
    DrawText("LVL 2 :", 40, 80, 30, BLACK);
    DrawText("LVL 3 :", 40, 115, 30, BLACK);
    DrawText("LVL 4 :", 40, 150, 30, BLACK);
    DrawText("LVL 5 :", 40, 185, 30, BLACK);
    DrawText("LVL 6 :", 40, 220, 30, BLACK);
    DrawText("LVL 7 :", 40, 255, 30, BLACK);
    DrawText("LVL 8 :", 40, 290, 30, BLACK);
    for (int i = 1; i <= listLvl.size(); i++) {
        DrawText((std::to_string(listLvl[i])).c_str(), 150, y, 30, BLACK);
        y += 35;
    }
}   