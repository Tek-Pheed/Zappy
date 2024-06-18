/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Menu
*/

#pragma once

#include <iostream>
#include "Draw.hpp"
#include "raylib.h"
#include "ServerData.hpp"
#include <string>

namespace Zappy {
    enum Scene {
        MENU,
        GAME,
        SETTINGS,
    };

    enum Shape {
        RECTANGLE,
        CIRCLE_SHAPE
    };

class Menu {

#define MAX_INPUT_CHARS     15

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
        void GameScene(Model model, Vector3 position, BoundingBox bounds, Zappy::Server server);
        void TextBoxForIp(Rectangle textBox, bool mouseOnText, char ip[MAX_INPUT_CHARS + 1], int letterCount, int framesCounter);
        void LoopForTextboxIp(Rectangle textBox, bool &mouseOnText, char ip[MAX_INPUT_CHARS + 1], int &letterCount, int &framesCounter);
        void TextBoxForPort(Rectangle textBox, bool mouseOnText, char port[MAX_INPUT_CHARS + 1], int letterCount, int framesCounter);
        void LoopForTextboxPort(Rectangle textBox, bool &mouseOnText, char port[MAX_INPUT_CHARS + 1], int &letterCount, int &framesCounter);
    protected:
    private:
        std::string _host;
        std::string _port;
};


class TextInput {
    public:
        TextInput(float x, float y, float width, float height);
        void UpdateInput();
        void DrawInput();
        std::string GetText() const;

    private:
        Rectangle bounds;
        std::string text;
        int letterCount;
        bool mouseOnText;
        int framesCounter;
    };

class ConfirmButton {
    public:
        bool createButton(float width, float height, float posX, float posY, float borderThickness, Color borderColor, Color hoverColor, Color pressColor, const char* text, float textSize, Color textColor, Shape shape, bool &clicked);
    };
}
