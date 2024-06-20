/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Thread.cpp
*/

#include <thread>
#include "Thread.hpp"
#include "RessourcePool.hpp"

Zappy::Thread::Thread()
{
    _running = true;
}

Zappy::Thread::~Thread(){}

void Zappy::Thread::ManageServer(Server &s, Parser &p, RessourceManager &objectPool)
{
    while (_running) {
        s.receiveMess();
        p.parsing(objectPool, s.getData());
        s.popData();
    }
}

void Zappy::Thread::setRunningFalse()
{
    _running = false;
}
