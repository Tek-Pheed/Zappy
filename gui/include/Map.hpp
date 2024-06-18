/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#pragma once
#include <list>
#include <vector>
#include "Items.hpp"
#include "Player.hpp"
#include <unordered_map>

namespace Zappy
{

    class Bloc {
      public:
        Bloc(int x, int y);
        ~Bloc();

        int getX() const;
        int getY() const;
        void setX(int X);
        void setY(int Y);

        void addItem(Zappy::items item, size_t quantity);
        void removeItem(Zappy::items item, size_t quantity);
        void setItems(std::vector<Zappy::items> items);
        std::vector<Zappy::items> getItems();

        void setPlayers(std::vector<Zappy::Player> players);
        std::vector<Zappy::Player> getPlayers();
        void display();

      private:
        int _x;
        int _y;
        std::unordered_map<enum items, size_t> _items;
        std::vector<Zappy::Player> _players;
    };

    class Map {
      public:
        Map();
        ~Map();
        void pushBloc(Bloc *bloc);
        std::list<Bloc *> getBloc();
        void setBloc(std::list<Bloc *> blocs);
        void setX(int x);
        void setY(int y);
        int getX();
        int getY();
        void drawMap();

      private:
        int _x;
        int _y;
        std::list<Bloc *> _bloc;
    };
} // namespace Zappy
