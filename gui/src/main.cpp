/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** main.cpp
*/

#include <iostream>
#include "raylib.h"
#include "Menu.hpp"
#include "Draw.hpp"
#include "../include/ServerData.hpp"

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    Model model;
    Zappy::Draw draw;
    Zappy::Menu menu;
    Texture2D texture_body, texture_leaf;

    if (!menu.InitWindowAndResources(screenWidth, screenHeight)) {
        std::cerr << "Erreur : Impossible d'initialiser la fenêtre et les ressources." << std::endl;
        return 1;
    }

    menu.LoadResources(model, texture_body, texture_leaf);

    Camera camera;
    menu.ConfigureCamera(camera);

    Vector3 position = { 0.0f, 0.0f, 0.0f };
    BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);

    Texture2D background = LoadTexture("assets/background.png");

    menu.MainLoop(model, background, camera, position, bounds, draw);

    menu.UnloadResources(model, texture_body, texture_leaf);
    return 0;
}
