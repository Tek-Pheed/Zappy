/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** main.cpp
*/

#include "gui/include/Utils.hpp"
#include "raylib.h"

int main()
{
    Zappy::Utils u;
    const int screenWidth = 800;
    const int screenHeight = 450;
    bool btnClick = false;

    InitWindow(screenWidth, screenHeight, "Raylib [core] example - basic window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        u.createButton(70, 50, 400,100, 40, BLACK, GREEN, PINK, "bouton", 10, WHITE, Zappy::ButtonShape::RECT, btnClick);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}