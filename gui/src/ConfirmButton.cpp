/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ConfirmButton
*/

#include "Menu.hpp"

bool Zappy::ConfirmButton::createButton(float width, float height, float posX,
    float posY, float borderThickness, Color borderColor, Color hoverColor,
    Color pressColor, const char *text, float textSize, Color textColor, bool &clicked)
{
    Rectangle buttonRect = {posX, posY, width, height};
    Vector2 mousePoint = GetMousePosition();
    bool isHovered = CheckCollisionPointRec(mousePoint, buttonRect);
    bool isPressed = isHovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    bool isReleased = isHovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

    if (isReleased) {
        clicked = true;
    }

    Color currentColor =
        isPressed ? pressColor : (isHovered ? hoverColor : borderColor);
    DrawRectangleLinesEx(buttonRect, borderThickness, currentColor);
    DrawText(text, posX + (width - MeasureText(text, textSize)) / 2,
        posY + (height - textSize) / 2, textSize, textColor);

    return isReleased;
}
