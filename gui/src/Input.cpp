/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Input
*/

#include "../include/Menu.hpp"

Zappy::TextInput::TextInput(float x, float y, float width, float height)
    : bounds{ x, y, width, height }, text(""), letterCount(0), mouseOnText(false), framesCounter(0) {}

void Zappy::TextInput::UpdateInput() {
    if (CheckCollisionPointRec(GetMousePosition(), bounds)) {
        mouseOnText = true;
    } else {
        mouseOnText = false;
    }

    if (mouseOnText) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
                text.push_back((char)key);
                letterCount++;
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            letterCount--;
            if (letterCount < 0) {
                letterCount = 0;
            }
            if (!text.empty()) {
                text.pop_back();
            }
        }
    }
    framesCounter++;
}

void Zappy::TextInput::DrawInput()
{
    DrawRectangleRec(bounds, LIGHTGRAY);
    if (mouseOnText) {
        DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, WHITE);
    } else {
        DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, DARKGRAY);
    }
    DrawText(text.c_str(), bounds.x + 5, bounds.y + 7, 40, BLACK);

    if (mouseOnText && ((framesCounter / 20) % 2 == 0)) {
        float textWidth = MeasureText(text.c_str(), 40);
        DrawText("_", bounds.x + 5 + textWidth, bounds.y + 7, 40, BLACK);
    }
}

std::string Zappy::TextInput::GetText() const {
    return text;
}