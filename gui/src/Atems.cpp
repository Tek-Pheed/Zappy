#include "IItems.hpp"


Zappy::Atems::Atems(float density, std::map<std::string, int> position,
   std::vector<std::map<std::string, int>> sameItems, const char *model,
   const char *texture, Utils &u) : _density(density), _position(position), _sameItems(sameItems), _u(u)
{
   _model = _u.createModel(texture, model);
}

Zappy::Atems::~Atems()
{
}

void Zappy::Atems::setDensity(float density)
{
   _density = density;
}

void Zappy::Atems::setPosition(std::map<std::string, int> position)
{
   _position = position;
}

void Zappy::Atems::addSameItems(std::map<std::string, int> position)
{
   _sameItems.push_back(position);
}

float Zappy::Atems::getDensity()
{
   return _density;
}

std::map<std::string, int> Zappy::Atems::getPosition()
{
   return _position;
}

std::vector<std::map<std::string, int>> Zappy::Atems::getSameItems()
{
   return _sameItems;
}

void Zappy::Atems::setModel(const char *texture, const char *model)
{
   _model = _u.createModel(model, texture);
}

Model Zappy::Atems::getModel()
{
   return _model;
}
