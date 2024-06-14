/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IItems
*/

#pragma once

#include <map>
#include <raylib.h>
#include <string>
#include <vector>
#include "Utils.hpp"

namespace Zappy
{

    enum items {
        food = 0,
        linemate = 1,
        deraumere = 2,
        sibur = 3,
        mendiane = 4,
        phiras = 5,
        thystame = 6
    };
    
    class IItems {
      public:
        virtual ~IItems() = default;
        virtual Zappy::items getItem() = 0;
    };

    class AItems : public IItems {
      private:
        std::vector<std::map<std::string, int>> _sameItems;
        Model _model;
        Zappy::items _item;

      public:
        AItems(Zappy::items item);
        ~AItems();
        Zappy::items getItem() override;
    };

    class Deraumere : public AItems {
      public:
        Deraumere(Zappy::items item);
        ~Deraumere();
    };

    class Food : public AItems {
      public:
        Food(/*std::vector<std::map<std::string, int>> sameItems,*/
            Zappy::items item);
        ~Food();
    };

    class Linemate : public AItems {
      public:
        Linemate(/*std::vector<std::map<std::string, int>> sameItems,*/
            Zappy::items item);
        ~Linemate();
    };

    class Mendiane : public AItems {
      public:
        Mendiane(/*std::vector<std::map<std::string, int>> sameItems,*/
            Zappy::items item);
        ~Mendiane();
    };

    class Phiras : public AItems {
      public:
        Phiras(/*std::vector<std::map<std::string, int>> sameItems,*/
            Zappy::items item);
        ~Phiras();
    };

    class Sibur : public AItems {
      public:
        Sibur(/*std::vector<std::map<std::string, int>> sameItems,*/
            Zappy::items item);
        ~Sibur();
    };

    class Thystame : public AItems {
      public:
        Thystame(/*std::vector<std::map<std::string, int>> sameItems,*/
            Zappy::items item);
        ~Thystame();
    };
} // namespace Zappy
