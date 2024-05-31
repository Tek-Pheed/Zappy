/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Utils.cpp
*/

#include "../include/Utils.hpp"

Zappy::Utils::Utils()
{
}

Zappy::Utils::~Utils()
{
}
  
Model Zappy::Utils::createModel(const char *model, const char *texture)
{
   Model model_body = LoadModel(model);
   Texture2D texture_body = LoadTexture(texture);

   model_body.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_body;
   return model_body;
}
