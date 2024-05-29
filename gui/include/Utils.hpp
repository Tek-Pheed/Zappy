/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Utils
*/

#pragma once
#include <iostream>
#include "raylib.h"

namespace Zappy {
    enum ButtonShape {
        CIRCLE,
        RECT
    };
    class Utils {
        public:
            Utils();
            ~Utils();
            void setTexture();
            void createButton(float sizeX, float sizeY, float posX, float posY, int r, Color buttonColor, Color hoverColor, Color clickColor, std::string name, int fontSize, Color txtColor, ButtonShape shape, bool &clicked);

        private:
    };
}

