/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Settings.cpp
*/

#include "../include/Settings.hpp"
#include "../include/Draw.hpp"

Zappy::Settings::Settings(){}

Zappy::Settings::~Settings(){}

void Zappy::Settings::setSound(int sound)
{
    _sound = sound;
}

int Zappy::Settings::getSound()
{
    return _sound;
}

void Zappy::Settings::setResolution(Resolution resolution)
{
    _resolution = resolution;
}

Zappy::Resolution Zappy::Settings::getResolution()
{
    return _resolution;
}

void Zappy::Settings::manageSettingsButton(bool &isClick, bool &resIsClick)
{
    Draw d;
    int Settingsclick = 0;
    int resolutionClick = 0;
    std::queue<std::string> resolutionName;
    std::deque<int> resolutionChoose;

    resolutionName.push("1280 x 720");
    resolutionName.push("1366 x 768");
    resolutionName.push("1600 x 900");
    resolutionName.push("1920 x 1080");
    resolutionName.push("2560 x 1440");
    resolutionName.push("3840 x 2160");

    for (int i = 0; i < resolutionName.size(); i++)
        resolutionChoose.push_back(0);

    d.createButton(70, 50, 10, 10, 0, GRAY, LIGHTGRAY, DARKGRAY, "Settings", 10, BLACK, ButtonShape::RECT, Settingsclick);
    if (Settingsclick)
        isClick = !isClick;
    if (isClick) {
        d.drawRectangle(250, 300, 400, 100, GRAY);
        DrawTextEx(GetFontDefault(), "Resolution :", (Vector2) {410, 110}, 20, 1, BLACK);
        d.createButton(100, 30, 530, 105, 0, WHITE, GREEN, PINK, "Change resolution", 10, BLACK, ButtonShape::RECT, resolutionClick);
        if (resolutionClick)
            resIsClick = !resIsClick;
        if (resIsClick) {
            d.createDropdownList(100, 30, 530, 135, WHITE, GREEN, PINK, BLACK, 10, resolutionChoose, resolutionName);
            changeResolution(resolutionChoose);
        }
    }
}

void Zappy::Settings::changeResolution(std::deque<int> resClick)
{
    std::deque<int> resIsClick = resClick;

    for(size_t i = 0; i < resClick.size(); i++) {
        if (resClick.at(i)) {
            if (i == 0) {
                SetWindowSize(1280, 720);
            }
            if (i == 1)
                SetWindowSize(1366, 768);
            if (i == 2)
                SetWindowSize(1600, 900);
            if (i == 3)
                SetWindowSize(1920, 1080);
            if (i == 4)
                SetWindowSize(2560, 1440);
            if (i == 5) {
                SetWindowSize(3840, 2160);
            }
        }
    }
}

void Zappy::Settings::openSettingsInterface()
{
    
}