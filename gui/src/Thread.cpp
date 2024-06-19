/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Thread.cpp
*/

#include <thread>
#include "Thread.hpp"
#include "RessourcePool.hpp"

Zappy::Thread::Thread(){}

Zappy::Thread::~Thread(){}

void Zappy::Thread::ManageServer(Server &s, Parser &p, RessourceManager &objectPool)
{
    while (1) {
        s.receiveMess();
        p.parsing(objectPool, s.getData());
    }
}
