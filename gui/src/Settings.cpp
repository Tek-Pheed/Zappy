/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Settings.cpp
*/

#include <string>
#include "Settings.hpp"
#include <cmath>

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

void Zappy::Settings::manageSettingsButton(bool &resIsClick, Music music, double &volume)
{
    Draw d;
    d.drawRectangle(360, 210, 755, 295, BLACK);
    d.drawRectangle(350, 200, 760, 300, GRAY);
    manageResolution(d, resIsClick);
    manageSoundMusic(music, d, volume, resIsClick);
}

void Zappy::Settings::manageSoundMusic(Music music, Draw d, double &volume, bool &resIsClick)
{
    int clickVolM = 0;
    int clickVolP = 0;
    int isClickVolM = 0;
    int isClickVolP = 0;
    (void) music;

    DrawTextEx(GetFontDefault(), "Volume music :", (Vector2) {780, 430}, 25, 1, BLACK);
    if (!resIsClick) {
        d.drawTextClick(960, 420, 50, BLACK, WHITE, WHITE, "-", clickVolM);
        DrawTextEx(GetFontDefault(), std::to_string(static_cast<int>(std::round(volume * 100))).c_str(), (Vector2){1010, 430}, 25, 1, BLACK);
        d.drawTextClick(1060, 420, 50, BLACK, WHITE, WHITE, "+", clickVolP);
        if (clickVolM){
            isClickVolM = !isClickVolM;
        }
        if (isClickVolM && volume > 0.1){
            volume -= 0.1;
        }
        if (clickVolP)
            isClickVolP = !isClickVolP;
        if (isClickVolP && volume < 0.9) {
            volume += 0.1;
        }
    }
}

void Zappy::Settings::manageResolution(Draw d, bool &resIsClick)
{
    int resolutionClick = 0;
    std::queue<std::string> resolutionName;
    std::deque<int> resolutionChoose;

    resolutionName.push("1280 x 720");
    resolutionName.push("1366 x 768");
    resolutionName.push("1600 x 900");
    resolutionName.push("1920 x 1080");
    resolutionName.push("2560 x 1440");
    resolutionName.push("3840 x 2160");

    for (size_t i = 0; i < resolutionName.size(); i++)
        resolutionChoose.push_back(0);

    DrawTextEx(GetFontDefault(), "Resolution :", (Vector2) {780, 340}, 25, 1, BLACK);
    d.createButton(150, 50, 950, 330, 0, BLACK, WHITE, WHITE, "Change resolution", 15, WHITE, ButtonShape::RECT, resolutionClick);
    if (resolutionClick)
        resIsClick = !resIsClick;
    if (resIsClick) {
        d.createDropdownList(150, 50, 950, 380, BLACK, WHITE, WHITE, BLACK, 15, resolutionChoose, resolutionName);
        changeResolution(resolutionChoose);
    }
}

void Zappy::Settings::changeResolution(std::deque<int> resClick)
{
    std::deque<int> resIsClick = resClick;

    for(size_t i = 0; i < resClick.size(); i++) {
        if (resClick.at(i)) {
            if (i == 0)
                SetWindowSize(1280, 720);
            if (i == 1)
                SetWindowSize(1366, 768);
            if (i == 2)
                SetWindowSize(1600, 900);
            if (i == 3)
                SetWindowSize(1920, 1080);
            if (i == 4)
                SetWindowSize(2560, 1440);
            if (i == 5)
                SetWindowSize(3840, 2160);
        }
    }
}

void Zappy::Settings::openSettingsInterface()
{
    
}