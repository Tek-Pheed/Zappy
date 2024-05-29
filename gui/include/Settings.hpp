/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Settings
*/

#pragma once

namespace Zappy {
class Settings {
    public:
        Settings();
        ~Settings();
        void setSound(int sound);
        int getSound();
        void setResolution(Resolution resolution);
        void changeResolution();
        void createSettingsButton();
        Resolution getResolution();

    private:
        int _sound;
        Resolution _resolution;
};

enum Resolution {
    RES_1920_1080,
    RES_1280_720,
    RES_800_600,
    RES_640_480
};
}
