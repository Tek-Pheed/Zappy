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
        void setResolution(_resolution resolution);
        _resolution getResolution();

    protected:
    private:
        int _sound;
};

enum _resolution {
    RES_1920_1080 = 0,
    RES_1280_720 = 1,
    RES_800_600 = 2,
    RES_640_480 = 3
};
}
