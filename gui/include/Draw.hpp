/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Draw
*/

#pragma once
#include <iostream>
#include "raylib.h"
#include <queue>

namespace Zappy {

    enum ButtonShape {
        CIRCLE,
        RECT
    };
class Draw {
    public:
        Draw();
        ~Draw();
        void drawRectangle(float sizeX, float sizeY, float posX, float posY, Color clr);
        void drawCircle(float posX, float posY, int r, Color clr);
        void drawPlateform3d();
        void draw3DModel();
        void createButton(float sizeX, float sizeY, float posX, float posY, int r, Color buttonColor, Color hoverColor, Color clickColor, std::string name, int fontSize, Color txtColor, ButtonShape shape, int &clicked);
        void createDropdownList(int sizeX, int sizeY, int posX, int posY, Color buttonColor, Color hoverColor, Color clickColor, Color txtColor, int fontSize, std::deque<int> &clickedList, std::queue<std::string> nameList);
        void drawTextClick(float posX, float posY, int fontSize, Color txtClr, Color hoverColor, Color clickColor, std::string txt, int &clicked);

    protected:
    private:
};
}
