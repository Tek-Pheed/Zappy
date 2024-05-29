/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Settings.cpp
*/

#include "../include/Settings.hpp"

namespace Zappy {

    Settings::Settings(){}

    Settings::Settings(){}

    void Settings::setSound(int sound)
    {
        _sound = sound;
    }

    int Settings::getSound()
    {
        return _sound;
    }

    void Settings::setResolution(Resolution resolution)
    {
        _resolution = resolution;
    }

    Resolution Settings::getResolution()
    {
        return _resolution;
    }
}
