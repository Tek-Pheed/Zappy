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

    void Draw::drawRectangle(float sizeX, float sizeY, float posX, float posY, Color clr)
    {
        Rectangle rect = {posX, posY, sizeX, sizeY};
        DrawRectangleRec(rect, clr);
    }

    void Draw::drawCircle(float posX, float posY, int r, Color clr)
    {
        Vector2 circle = {posX, posY};
        DrawCircleV(circle, r, clr);
    }

    void Draw::drawPlateform3d(){}
    void Draw::draw3DModel(){}

    void Draw::createButton(float sizeX, float sizeY, float posX, float posY, int r, Color buttonColor, Color hoverColor, Color clickColor, std::string name, int fontSize, Color txtColor, ButtonShape shape, int &clicked)
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
                clicked = (clicked == 1 ? 0 : 1);
            else
                color = hoverColor;
        } else {
            color = buttonColor;
        }
        if (color.r == BLACK.r && color.g == BLACK.g && color.b == BLACK.b && color.a == BLACK.a && txtColor.r == BLACK.r && txtColor.g == BLACK.g && txtColor.b == BLACK.b && txtColor.a == BLACK.a)
            txtColor = WHITE;
        if (color.r == WHITE.r && color.g == WHITE.g && color.b == WHITE.b && color.a == WHITE.a && txtColor.r == WHITE.r && txtColor.g == WHITE.g && txtColor.b == WHITE.b && txtColor.a == WHITE.a)
            txtColor = BLACK;
        if (shape == ButtonShape::CIRCLE)
            DrawCircleV(buttonPosC, r, color);
        else
            DrawRectangleRec(buttonPosR, color);
        if (name != "")
            DrawTextEx(GetFontDefault(), name.c_str(), (Vector2){textX, textY}, fontSize, 1, txtColor);
    }
}

void Zappy::Draw::createDropdownList(int sizeX, int sizeY, int posX, int posY, Color buttonColor, Color hoverColor, Color clickColor, Color txtColor, int fontSize, std::deque<int> &clickedList, std::queue<std::string> nameList)
{
    int newPosX = posX;
    int newPosY = posY;

    for (size_t i = 0; i < clickedList.size(); i++) {
        createButton(sizeX, sizeY, newPosX, newPosY, 0, buttonColor, hoverColor, clickColor, nameList.front(), fontSize, txtColor, ButtonShape::RECT, clickedList.at(i));
        newPosY = newPosY + sizeY;
        nameList.pop();
    }
}

void Zappy::Draw::drawTextClick(float posX, float posY, int fontSize, Color txtClr, Color hoverColor, Color clickColor, std::string txt, int &clicked)
{
    bool mouseOverButton;
    Vector2 txtSizeV = MeasureTextEx(GetFontDefault(), txt.c_str(), fontSize, 1);
    Rectangle rect = {posX, posY, txtSizeV.x, txtSizeV.y};
    Color color;

    mouseOverButton = CheckCollisionPointRec(GetMousePosition(), rect);
    if (mouseOverButton) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            color = clickColor;
        else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            clicked = (clicked == 1 ? 0 : 1);
        else
            color = hoverColor;
    } else
        color = txtClr;
    DrawTextEx(GetFontDefault(), txt.c_str(), (Vector2){posX, posY}, fontSize, 1, color);
}