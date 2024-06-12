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
    class IItems {
      public:
        virtual ~IItems() = default;
        // virtual std::vector<std::map<std::string, int>> getSameItems() = 0;
        // virtual void addSameItems(std::map<std::string, int> position) = 0;
        // void RemoveItems(int amount); ???? a voir si on en a besoin
        virtual void setModel(const char *texture, const char *model) = 0;
        virtual Model getModel() = 0;
    };

    enum items {
        food = 0,
        linemate = 1,
        deraumere = 2,
        sibur = 3,
        mendiane = 4,
        phiras = 5,
        thystame = 6
    };

    class AItems : public IItems {
      private:
        std::vector<std::map<std::string, int>> _sameItems;
        Model _model;
        Utils &_u;

      public:
        AItems(/*std::vector<std::map<std::string, int>> sameItems,*/
            const char *model, const char *texture, Utils &u);
        ~AItems();
        // std::vector<std::map<std::string, int>> getSameItems() override;
        // void addSameItems(std::map<std::string, int> position) override;
        void setModel(const char *texture, const char *model) override;
        Model getModel() override;
    };

    class Deraumere : public AItems {
      public:
        Deraumere(/*std::vector<std::map<std::string, int>> sameItems,*/
            const char *model, const char *texture, Utils &u);
        ~Deraumere();
    };

    class Food : public AItems {
      public:
        Food(/*std::vector<std::map<std::string, int>> sameItems,*/
            const char *model, const char *texture, Utils &u);
        ~Food();
    };

    class Linemate : public AItems {
      public:
        Linemate(/*std::vector<std::map<std::string, int>> sameItems,*/
            const char *model, const char *texture, Utils &u);
        ~Linemate();
    };

    class Mendiane : public AItems {
      public:
        Mendiane(/*std::vector<std::map<std::string, int>> sameItems,*/
            const char *model, const char *texture, Utils &u);
        ~Mendiane();
    };

    class Phiras : public AItems {
      public:
        Phiras(/*std::vector<std::map<std::string, int>> sameItems,*/
            const char *model, const char *texture, Utils &u);
        ~Phiras();
    };

    class Sibur : public AItems {
      public:
        Sibur(/*std::vector<std::map<std::string, int>> sameItems,*/
            const char *model, const char *texture, Utils &u);
        ~Sibur();
    };

    class Thystame : public AItems {
      public:
        Thystame(/*std::vector<std::map<std::string, int>> sameItems,*/
            const char *model, const char *texture, Utils &u);
        ~Thystame();
    };
} // namespace Zappy
