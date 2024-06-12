#include "Items.hpp"

Zappy::AItems::AItems(float density, std::map<std::string, int> position,
    std::vector<std::map<std::string, int>> sameItems, const char *model,
    const char *texture, Utils &u)
    : _density(density), _position(position), _sameItems(sameItems), _u(u)
{
    _model = _u.createModel(texture, model);
}

Zappy::AItems::~AItems()
{
}

void Zappy::AItems::setDensity(float density)
{
    _density = density;
}

void Zappy::AItems::setPosition(std::map<std::string, int> position)
{
    _position = position;
}

void Zappy::AItems::addSameItems(std::map<std::string, int> position)
{
    _sameItems.push_back(position);
}

float Zappy::AItems::getDensity()
{
    return _density;
}

std::map<std::string, int> Zappy::AItems::getPosition()
{
    return _position;
}

std::vector<std::map<std::string, int>> Zappy::AItems::getSameItems()
{
    return _sameItems;
}

void Zappy::AItems::setModel(const char *texture, const char *model)
{
    _model = _u.createModel(model, texture);
}

Model Zappy::AItems::getModel()
{
    return _model;
}
