/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Graphics
*/

#pragma once

#include <vector>
#include "Items.hpp"
#include "Player.hpp"

namespace Zappy
{
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
} // namespace Zappy
