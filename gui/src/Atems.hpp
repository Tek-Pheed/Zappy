/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Atems.hpp
*/

#include "IItems.hpp"

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
