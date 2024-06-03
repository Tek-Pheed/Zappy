/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IpInput
*/

#include "../include/Menu.hpp"

void Zappy::Menu::TextBoxForIp(Rectangle textBox, bool mouseOnText, char ip[MAX_INPUT_CHARS + 1], int letterCount, int framesCounter)
{
    if (mouseOnText) {
        framesCounter++;
    } else {
        framesCounter = 0;
    }

    DrawText("Entry IP", 1350, 60, 20, WHITE);
    DrawRectangleRec(textBox, LIGHTGRAY);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
    DrawText(ip, (int)textBox.x + 5, (int)textBox.y + 8, 40, BLACK);

    if (mouseOnText) {
        if (letterCount < MAX_INPUT_CHARS) {
            if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(ip, 40), (int)textBox.y + 12, 40, BLACK);
        } else {
            DrawText("Press BACKSPACE to delete chars...", 1350, 300, 20, WHITE);
        }
    }
}

void Zappy::Menu::LoopForTextboxIp(Rectangle textBox, bool &mouseOnText, char ip[MAX_INPUT_CHARS + 1], int &letterCount, int &framesCounter)
{
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
    else mouseOnText = false;

    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        int key = GetKeyPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
                ip[letterCount] = (char)key;
                ip[letterCount + 1] = '\0';
                letterCount++;
            }
            key = GetKeyPressed();
        }

        if (IsKeyDown(KEY_BACKSPACE)) {
            framesCounter++;
            if (framesCounter % 5 == 0) {  // Adjust the delay to your needs
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                ip[letterCount] = '\0';
            }
        } else {
            framesCounter = 0;
        }
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    TextBoxForIp(textBox, mouseOnText, ip, letterCount, framesCounter);
}
