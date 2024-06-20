/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Thread.hpp
*/

#pragma once
#include "Menu.hpp"
#include "ServerData.hpp"

namespace Zappy
{
    class Thread {
        public:
            Thread();
            ~Thread();
            void ManageServer(
              Zappy::Server &s, Zappy::Parser &p, RessourceManager &objectPool);
            void setRunningFalse();
        private:
            bool _running;
    };
} // namespace Zappy
