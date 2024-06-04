/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** main.cpp
*/

#include "Draw.hpp"
#include "Settings.hpp"
#include "raylib.h"

int main()
{
    Zappy::Settings s;
    const int screenWidth = 800;
    const int screenHeight = 450;
    bool btnClick = false;
    bool resIsClick = false;
    double volume = 0.5;

    InitWindow(screenWidth, screenHeight, "Raylib [core] example - basic window");
    InitAudioDevice();
    Music music = LoadMusicStream("test.mp3");
    SetMusicVolume(music, volume);
    PlayMusicStream(music);
    

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        s.manageSettingsButton(btnClick, resIsClick, music, volume);
        UpdateMusicStream(music);
        EndDrawing();
    }
    UnloadMusicStream(music);
    CloseWindow();

    return 0;
}
