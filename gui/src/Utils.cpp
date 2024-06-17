/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Utils.cpp
*/

#include "Utils.hpp"

Zappy::Utils::Utils()
{
}

Zappy::Utils::~Utils()
{
}

Model Zappy::Utils::createModel(const char *model)
{
   Model model_body = LoadModel(model);

   return model_body;
}
