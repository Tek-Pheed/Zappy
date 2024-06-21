/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Mouse
*/

#include <utility>
#include "Menu.hpp"

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

class Mouse {
    public:
        Mouse(float tileWidth, float tileHeight, int gridWidth, int gridHeight);
        std::pair<int, int> GetTileAtMouse();
    private:
        float _tileWidth;
        float _tileHeight;
        int _gridWidth;
        int _gridHeight;
};

#endif /* !MOUSE_HPP_ */
