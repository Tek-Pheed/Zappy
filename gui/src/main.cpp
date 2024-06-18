/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** main.cpp
*/

#include <iostream>
#include "Draw.hpp"
#include "Menu.hpp"
#include "RessourcePool.hpp"
#include "raylib.h"

int main(void)
{
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    RessourceManager objectPool;
    Zappy::Draw draw;
    Zappy::Menu menu;
    Camera camera;
    Vector3 position = {0.0f, 0.0f, 0.0f};

    srand(time(0));
    if (!menu.InitWindowAndResources(screenWidth, screenHeight)) {
        std::cerr << "Erreur : Impossible d'initialiser la fenêtre et les "
                     "ressources."
                  << std::endl;
        return 1;
    }
    menu.LoadResources(objectPool);
    menu.ConfigureCamera(camera);
    objectPool.textures.loadRessource("background", "assets/background.png");
    BoundingBox bounds =
        GetMeshBoundingBox(objectPool.models.getRessource("korok").meshes[0]);
    menu.MainLoop(objectPool, camera, position, bounds, draw);
    return 0;
}
