/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Menu
*/

#pragma once

#include <string>
#include "Draw.hpp"
#include "RessourcePool.hpp"
#include "ServerData.hpp"
#include "raylib.h"

#define MAX_INPUT_CHARS 9

namespace Zappy
{
    enum Scene {
        MENU,
        GAME,
        SETTINGS,
    };

    enum Shape { RECTANGLE, CIRCLE_SHAPE };

    class Menu {
      public:
        Menu();
        ~Menu();
        void setHost(std::string host);
        void setPort(std::string port);
        bool InitWindowAndResources(int screenWidth, int screenHeight);
        void LoadResources(RessourceManager &objectPool);
        void ConfigureCamera(Camera &camera);
        void MainLoop(RessourceManager &objectPool, Camera camera,
            Vector3 position, BoundingBox bounds, Zappy::Draw &draw);
        void LoopForTextbox(Rectangle textBox, bool &mouseOnText,
            char name[MAX_INPUT_CHARS + 1], int &letterCount,
            int &framesCounter);
        void GameScene(RessourceManager &objectPool, Vector3 position, BoundingBox bounds,
            Zappy::Server server, Music music);
        void TextBoxForIp(Rectangle textBox, bool mouseOnText,
            char ip[MAX_INPUT_CHARS + 1], int letterCount, int framesCounter);
        void LoopForTextboxIp(Rectangle textBox, bool &mouseOnText,
            char ip[MAX_INPUT_CHARS + 1], int &letterCount,
            int &framesCounter);
        void TextBoxForPort(Rectangle textBox, bool mouseOnText,
            char port[MAX_INPUT_CHARS + 1], int letterCount,
            int framesCounter);
        void LoopForTextboxPort(Rectangle textBox, bool &mouseOnText,
            char port[MAX_INPUT_CHARS + 1], int &letterCount,
            int &framesCounter);

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
        bool createButton(float width, float height, float posX, float posY,
            float borderThickness, Color borderColor, Color hoverColor,
            Color pressColor, const char *text, float textSize,
            Color textColor, Shape shape, bool &clicked);
    };
} // namespace Zappy
