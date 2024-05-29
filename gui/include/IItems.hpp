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
       virtual std::map<std::string, int> getPosition() = 0;
       virtual void setPosition(std::map<std::string, int> position) = 0;
       virtual float getDensity() = 0;
       virtual void setDensity(float density) = 0;
       virtual std::vector<std::map<std::string, int>> getSameItems() = 0;
       virtual void addSameItems(std::map<std::string, int> position) = 0;
       // void RemoveItems(int amount); ???? a voir si on en a besoin
       virtual void setModel(const char *texture, const char *model) = 0;
       virtual Model getModel() = 0;
   };

   enum items {
       Food = 0,
       Linemate = 1,
       Deraumere = 2,
       Sibur = 3,
       Mendiane = 4,
       Phiras = 5,
       Thystame = 6
   };

   class Atems : public IItems {
     private:
       float _density;
       std::map<std::string, int> _position;
       std::vector<std::map<std::string, int>> _sameItems;
       Model _model;
       Utils &_u;

     public:
       Atems(float density, std::map<std::string, int> position,
           std::vector<std::map<std::string, int>> sameItems,
           const char *model, const char *texture, Utils &u);
       ~Atems();
       std::map<std::string, int> getPosition() override;
       void setPosition(std::map<std::string, int> position) override;
       float getDensity() override;
       void setDensity(float density) override;
       std::vector<std::map<std::string, int>> getSameItems() override;
       void addSameItems(std::map<std::string, int> position) override;
       void setModel(const char *texture, const char *model) override;
       Model getModel() override;
   };

   class Deraumere : public Atems {
     public:
       Deraumere(float density, std::map<std::string, int> position,
           std::vector<std::map<std::string, int>> sameItems,
           const char *model, const char *texture, Utils &u);
       ~Deraumere();
   };

   class Food : public Atems {
     public:
       Food(float density, std::map<std::string, int> position,
           std::vector<std::map<std::string, int>> sameItems,
           const char *model, const char *texture, Utils &u);
       ~Food();
   };

   class Linemate : public Atems {
     public:
       Linemate(float density, std::map<std::string, int> position,
           std::vector<std::map<std::string, int>> sameItems,
           const char *model, const char *texture, Utils &u);
       ~Linemate();
   };

   class Mendiane : public Atems {
     public:
       Mendiane(float density, std::map<std::string, int> position,
           std::vector<std::map<std::string, int>> sameItems,
           const char *model, const char *texture, Utils &u);
       ~Mendiane();
   };

   class Phiras : public Atems {
     public:
       Phiras(float density, std::map<std::string, int> position,
           std::vector<std::map<std::string, int>> sameItems,
           const char *model, const char *texture, Utils &u);
       ~Phiras();
   };

   class Sibur : public Atems {
     public:
       Sibur(float density, std::map<std::string, int> position,
           std::vector<std::map<std::string, int>> sameItems,
           const char *model, const char *texture, Utils &u);
       ~Sibur();
   };

   class Thystame : public Atems {
     public:
       Thystame(float density, std::map<std::string, int> position,
           std::vector<std::map<std::string, int>> sameItems,
           const char *model, const char *texture, Utils &u);
       ~Thystame();
   };
} // namespace Zappy
