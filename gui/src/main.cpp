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

void print_help(char **args)
{
    std::string help("-help");

    if (args == NULL || args[1] == NULL) {
        std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
        exit(84);
    }
    if (help.compare(args[1]) == 0) {
        std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
        exit(0);
    }
}

void Zappy::Menu::getPort(char **args)
{
    for (int i = 0; args[i] != nullptr; i++) {
        if (std::string(args[i]) == "-p") {
            _port = args[i + 1];
        }
        if (std::string(args[i]) == "-h") {
            _host = args[i + 1];
        }
    }
}

int main(int ac, char **av)
{
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    RessourceManager objectPool;
    Zappy::Draw draw;
    Zappy::Menu menu;
    Camera camera;
    Vector3 position = {0.0f, 0.0f, 0.0f};

    print_help(av);
    if (ac < 5) {
        std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
        exit(84);
    }
    menu.getPort(av);

    if (!menu.InitWindowAndResources(screenWidth, screenHeight)) {
        std::cerr << "Erreur : Impossible d'initialiser la fenêtre et les "
                     "ressources."
                  << std::endl;
        return 1;
    }
    menu.LoadResources(objectPool);
    menu.ConfigureCamera(camera);
    BoundingBox bounds =
        GetMeshBoundingBox(objectPool.models.getRessource("korok").meshes[0]);
    menu.MainLoop(objectPool, camera, position, bounds, draw);
    return 0;
}
