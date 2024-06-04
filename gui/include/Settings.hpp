/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Settings
*/

#pragma once
#include <queue>
#include "raylib.h"
#include "Draw.hpp"

namespace Zappy {

    enum Resolution {
        RES_1920_1080,
        RES_1280_720,
        RES_800_600,
        RES_640_480
    };
    class Settings {
        public:
            Settings();
            ~Settings();
            void setSound(int sound);
            int getSound();
            void setResolution(Resolution resolution);
            void manageSettingsButton(bool &resIsClick, Music music, double &volume);
            void manageSoundMusic(Music music, Draw d, double &volume);
            void changeResolution(std::deque<int> resClick);
            void manageResolution(Draw d, bool &resIsClick);
            Resolution getResolution();
            void openSettingsInterface();

        private:
            int _sound;
            Resolution _resolution;
    };
}
