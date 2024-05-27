/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Graphics
*/

#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#include <vector>
#include "Player.hpp"
#include "IItems.hpp"

class Graphics {
    public:
        Graphics();
        ~Graphics();
        void draw();
        void createWindow();
        // all getters and setters a faire

    protected:
    private:
        std::vector<Player> _players;
        // _component;
        std::vector<IItems> _items;
        // _window;
};

#endif /* !GRAPHICS_HPP_ */
