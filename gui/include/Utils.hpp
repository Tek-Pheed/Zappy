/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Utils
*/
#pragma once

#include <iostream>
#include "raylib.h"

namespace Zappy {
   class Utils {
       public:
           Utils();
           ~Utils();
           Camera createCamera();
           Model createModel(const char *model, const char *texture);
       private:
   };
}
