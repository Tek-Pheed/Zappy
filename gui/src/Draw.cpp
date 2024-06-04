/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Draw.cpp
*/

#include "Draw.hpp"

namespace Zappy {

    Draw::Draw(){}
    Draw::~Draw(){}
    void Draw::drawRectangle(){}
    void Draw::drawCircle(){}
    void Draw::drawPlateform3d(){}
    void Draw::draw3DModel(){}

    void Draw::createButton(float sizeX, float sizeY, float posX, float posY, int r, Color buttonColor, Color hoverColor, Color clickColor, std::string name, int fontSize, Color txtColor, ButtonShape shape, bool &clicked)
    {
        Vector2 mousePos = GetMousePosition();
        bool mouseOverButton;
        Color color;
        Vector2 buttonPosC;
        Rectangle buttonPosR;
        float textX;
        float textY;
        Vector2 textSize = MeasureTextEx(GetFontDefault(), name.c_str(), fontSize, 1);

        if (shape == ButtonShape::CIRCLE) {
            buttonPosC = {posX, posY};
            mouseOverButton = CheckCollisionPointCircle(mousePos, buttonPosC, r);
            textX = posX - textSize.x / 2.0f;
            textY = posY - textSize.y / 2.0f;
        } else {
            buttonPosR = {posX, posY, sizeX, sizeY};
            mouseOverButton = CheckCollisionPointRec(mousePos, buttonPosR);
            textX = buttonPosR.x + (buttonPosR.width - textSize.x) / 2.0f;
            textY = buttonPosR.y + (buttonPosR.height - textSize.y) / 2.0f;
        }
        if (mouseOverButton) {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                color = clickColor;
            else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                clicked = !clicked;
            else
                color = hoverColor;
        } else {
            color = buttonColor;
        }
        if (shape == ButtonShape::CIRCLE)
            DrawCircleV(buttonPosC, r, color);
        else
            DrawRectangleRec(buttonPosR, color);
        if (name.c_str() != "")
            DrawTextEx(GetFontDefault(), name.c_str(), (Vector2){textX, textY}, fontSize, 1, txtColor);
    }
}
