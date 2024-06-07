/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IItems
*/

#pragma once

#include <vector>
#include <string>
#include <map>

namespace Zappy {
class IItems {
    public:
        virtual ~IItems() = default;
        virtual std::map<std::string, int> getPosition() = 0;
        virtual void setPosition(std::map<std::string, int> position) = 0;
        virtual int GetAmount() = 0;
        virtual void SetAmount(int amount) = 0;
        virtual std::vector<std::map<std::string, int>> getSameItems() = 0;
        virtual void addSameItems(std::map<std::string, int> position) = 0;
        // void RemoveItems(int amount); ???? a voir si on en a besoin

    protected:
    private:
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

class Atems : public IItems
{
private:
    int _density;
    std::map<std::string, int> _position;
    std::vector<std::map<std::string, int>> _sameItems;
public:
    Atems(/* args */);
    ~Atems();
    std::map<std::string, int> getPosition() override;
    void setPosition(std::map<std::string, int> position) override;
    int GetAmount() override;
    void SetAmount(int amount) override;
    std::vector<std::map<std::string, int>> getSameItems() override;
    void addSameItems(std::map<std::string, int> position) override;
};

class Deraumere : public Atems
{
public:
    Deraumere(/* args */);
    ~Deraumere();
};

class Food : public Atems
{
public:
    Food(/* args */);
    ~Food();
};

class Linemate : public Atems
{
public:
    Linemate(/* args */);
    ~Linemate();
};

class Mendiane : public Atems
{
public:
    Mendiane(/* args */);
    ~Mendiane();
};

class Phiras : public Atems
{
public:
    Phiras(/* args */);
    ~Phiras();
};

class Sibur : public Atems
{
public:
    Sibur(/* args */);
    ~Sibur();
};

class Thystame : public Atems
{
public:
    Thystame(/* args */);
    ~Thystame();
};
}
