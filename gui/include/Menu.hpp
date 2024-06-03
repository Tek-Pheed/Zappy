/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Menu
*/

#pragma once

#include <iostream>
#include "Draw.hpp"

namespace Zappy {
    enum Scene {
        MENU,
        GAME,
        SETTINGS,
    };
class Menu {

#define MAX_INPUT_CHARS 9

    public:
        Menu();
        ~Menu();
        void setHost(std::string host);
        void setPort(std::string port);
        bool InitWindowAndResources(int screenWidth, int screenHeight);
        void LoadResources(Model &model, Texture2D &texture_body, Texture2D &texture_leaf);
        void ConfigureCamera(Camera &camera);
        void MainLoop(Model model, Texture2D background, Camera camera, Vector3 position, BoundingBox bounds, Zappy::Draw &draw);
        void UnloadResources(Model model, Texture2D texture_body, Texture2D texture_leaf);
        void LoopForTextbox(Rectangle textBox, bool &mouseOnText, char name[MAX_INPUT_CHARS + 1], int &letterCount, int &framesCounter);
        void TextBoxForPort(Rectangle textBox, bool mouseOnText, char port[MAX_INPUT_CHARS + 1], int letterCount, int framesCounter);
        void GameScene(Model model, Camera camera, Vector3 position, BoundingBox bounds);

    protected:
    private:
        std::string _host;
        std::string _port;
};
}
