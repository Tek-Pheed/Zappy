/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#pragma once

namespace Zappy {
class Map {
    public:
        Map();
        ~Map();
        void setX(int x);
        int getX();
        void setY(int y);
        int getY();

    protected:
    private:
        int _x;
        int _y;
};
}
