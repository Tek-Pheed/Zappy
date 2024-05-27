/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

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
    RES_1920_1080,
    RES_1280_720,
    RES_800_600,
    RES_640_480
};

#endif /* !SETTINGS_HPP_ */
