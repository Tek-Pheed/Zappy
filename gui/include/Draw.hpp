/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Draw
*/

#pragma once
#include <iostream>
#include "raylib.h"

namespace Zappy {

    enum ButtonShape {
        CIRCLE,
        RECT
    };
class Draw {
    public:
        Draw();
        ~Draw();
        void drawRectangle();
        void drawCircle();
        void drawPlateform3d();
        void draw3DModel();
        void createButton(float sizeX, float sizeY, float posX, float posY, int r, Color buttonColor, Color hoverColor, Color clickColor, std::string name, int fontSize, Color txtColor, ButtonShape shape, bool &clicked);

    protected:
    private:
};
}
